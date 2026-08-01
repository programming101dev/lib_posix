#include <dirent.h>
#include <errno.h>
#include <p101_c/p101_stdio.h>
#include <p101_c/p101_stdlib.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_posix/p101_dirent.h>
#include <p101_posix/p101_nl_types.h>
#include <p101_posix/p101_pthread.h>
#include <p101_posix/p101_regex.h>
#include <p101_posix/p101_stdio.h>
#include <p101_posix/p101_stdlib.h>
#include <p101_posix/p101_unistd.h>
#include <p101_posix/p101_wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

static int failures;

#define EXPECT(condition)                                                        \
    do                                                                           \
    {                                                                            \
        if(!(condition))                                                         \
        {                                                                        \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            failures++;                                                          \
        }                                                                        \
    } while(0)

struct event_counts
{
    int enters;
    int exits;
    int opens;
    int closes;
    int allocations;
    int frees;
};

struct resource_counts
{
    int mutex_acquires;
    int mutex_releases;
};

struct fault_state
{
    const char *target;
    int         checks;
};

static void observe_calls(const struct p101_env *env, p101_env_call_event event, const char *call_name, const char *arguments, const char *result, const char *file_name, const char *function_name, int line_number, void *user_data)
{
    struct event_counts *counts;

    (void)env;
    (void)call_name;
    (void)arguments;
    (void)result;
    (void)file_name;
    (void)function_name;
    (void)line_number;
    counts = user_data;
    if(event == P101_ENV_CALL_ENTER)
    {
        counts->enters++;
    }
    else
    {
        counts->exits++;
    }
}

static void observe_fds(const struct p101_env *env, p101_env_fd_event event, int fd, const char *file_name, const char *function_name, int line_number, void *user_data)
{
    struct event_counts *counts;

    (void)env;
    (void)fd;
    (void)file_name;
    (void)function_name;
    (void)line_number;
    counts = user_data;
    if(event == P101_ENV_FD_OPEN)
    {
        counts->opens++;
    }
    else
    {
        counts->closes++;
    }
}

static void observe_allocations(const struct p101_env *env, p101_env_alloc_event event, const void *ptr, const void *new_ptr, size_t size, const char *file_name, const char *function_name, int line_number, void *user_data)
{
    struct event_counts *counts;

    (void)env;
    (void)ptr;
    (void)new_ptr;
    (void)size;
    (void)file_name;
    (void)function_name;
    (void)line_number;
    counts = user_data;
    if(event == P101_ENV_ALLOC_ALLOC)
    {
        counts->allocations++;
    }
    else if(event == P101_ENV_ALLOC_FREE)
    {
        counts->frees++;
    }
}

static void observe_resources(const struct p101_env *env, p101_env_resource_kind event, const char *resource_class, const char *resource_id, const char *related_id, size_t size, const char *metadata, const char *file_name, const char *function_name, int line_number, void *user_data)
{
    struct resource_counts *counts;

    (void)env;
    (void)resource_id;
    (void)related_id;
    (void)size;
    (void)metadata;
    (void)file_name;
    (void)function_name;
    (void)line_number;
    counts = user_data;
    if(strcmp(resource_class, "pthread-mutex-held") != 0)
    {
        return;
    }
    if(event == P101_ENV_RESOURCE_ACQUIRE)
    {
        counts->mutex_acquires++;
    }
    else if(event == P101_ENV_RESOURCE_RELEASE)
    {
        counts->mutex_releases++;
    }
}

static int fail_named_call(const struct p101_env *env, const char *call_name, void *user_data)
{
    struct fault_state *state;

    (void)env;
    state = user_data;
    state->checks++;
    return (strcmp(call_name, state->target) == 0) ? ENOMEM : 0;
}

static void test_sentinel_contracts(struct p101_env *env, struct p101_error *err)
{
    const wchar_t    *wide_source;
    struct dirent     first  = {0};
    struct dirent     second = {0};
    mbstate_t         state  = {0};
    wchar_t          *wide_copy;
    char              multibyte[8];
    char              known_key[] = "known";
    char              options[] = "unknown=value";
    char             *keys[]    = {known_key, NULL};
    char             *cursor    = options;
    char             *value     = NULL;

    EXPECT(p101_getsubopt(env, &cursor, keys, &value) == -1);
    EXPECT(value != NULL && strcmp(value, "value") == 0);

    (void)strcpy(first.d_name, "z");
    (void)strcpy(second.d_name, "a");
    {
        const struct dirent *first_ptr  = &first;
        const struct dirent *second_ptr = &second;
        EXPECT(p101_alphasort(env, &first_ptr, &second_ptr) > 0);
    }

    wide_copy = p101_wcsdup(env, err, L"abc");
    EXPECT(wide_copy != NULL);
    EXPECT(p101_error_has_no_error(err));
    if(wide_copy != NULL)
    {
        p101_free(env, wide_copy);
    }

    wide_source = L"abc";
    EXPECT(p101_wcsnrtombs(env, err, multibyte, &wide_source, 3, sizeof(multibyte), &state) == 3);
    EXPECT(p101_error_has_no_error(err));

    EXPECT(p101_isatty(env, err, -1) == 0);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
}

static void test_eof_is_not_an_error(struct p101_env *env, struct p101_error *err)
{
    FILE   *stream;
    char   *line = NULL;
    size_t  size = 0;

    stream = p101_tmpfile(env, err);
    EXPECT(stream != NULL);
    EXPECT(p101_error_has_no_error(err));
    if(stream == NULL)
    {
        p101_error_reset(err);
        return;
    }

    EXPECT(p101_getline(env, err, &line, &size, stream) == -1);
    EXPECT(p101_error_has_no_error(err));
    if(line != NULL)
    {
        p101_free(env, line);
    }
    EXPECT(p101_fclose(env, err, stream) == 0);
}

static void test_resource_events(struct p101_env *env, struct p101_error *err)
{
    struct event_counts counts = {0};
    DIR                *directory;

    p101_env_set_fd_observer(env, observe_fds, &counts);
    directory = p101_opendir(env, err, ".");
    EXPECT(directory != NULL);
    EXPECT(counts.opens == 1);
    if(directory != NULL)
    {
        EXPECT(p101_closedir(env, err, directory) == 0);
        EXPECT(counts.closes == 1);
    }
    p101_env_set_fd_observer(env, NULL, NULL);
}

static void test_regex_error_message_cleanup(struct p101_env *env, struct p101_error *err)
{
    struct event_counts counts = {0};
    regex_t             expression;

    p101_env_set_alloc_observer(env, observe_allocations, &counts);
    P101_ERROR_RAISE_ERRNO(err, EBUSY);
    EXPECT(p101_regcomp(env, err, &expression, "[", REG_EXTENDED) != 0);
    EXPECT(counts.allocations == counts.frees);
    p101_error_reset(err);
    p101_env_set_alloc_observer(env, NULL, NULL);
}

static void test_expected_statuses(struct p101_env *env, struct p101_error *err)
{
    struct resource_counts counts = {0};
    pthread_mutex_t        mutex;

    p101_env_set_resource_observer(env, observe_resources, &counts);
    EXPECT(p101_pthread_mutex_init(env, err, &mutex, NULL) == 0);
    EXPECT(p101_pthread_mutex_lock(env, err, &mutex) == 0);
    EXPECT(p101_pthread_mutex_trylock(env, err, &mutex) == EBUSY);
    EXPECT(p101_error_has_no_error(err));
    EXPECT(p101_pthread_mutex_unlock(env, err, &mutex) == 0);
    EXPECT(p101_pthread_mutex_destroy(env, err, &mutex) == 0);
    EXPECT(counts.mutex_acquires == 1);
    EXPECT(counts.mutex_releases == 1);
    p101_env_set_resource_observer(env, NULL, NULL);
}

static void test_faults_and_balanced_trace(struct p101_env *env, struct p101_error *err)
{
    struct event_counts counts = {0};
    struct fault_state  fault  = {"access", 0};
    nl_catd             catalog;
    char                fallback[] = "fallback";

    p101_env_set_call_observer(env, observe_calls, &counts);
    p101_env_set_fault_injector(env, fail_named_call, &fault);
    counts.enters = 0;
    counts.exits  = 0;
    EXPECT(p101_access(env, err, ".", F_OK) == -1);
    EXPECT(p101_error_is_errno(err, ENOMEM));
    EXPECT(fault.checks == 1);
    EXPECT(counts.enters >= 1);
    EXPECT(counts.enters == counts.exits);
    p101_error_reset(err);

    memset(&catalog, 0, sizeof(catalog));
    fault.target = "catgets";
    EXPECT(p101_catgets(env, err, catalog, 1, 1, fallback) == fallback);
    EXPECT(p101_error_is_errno(err, ENOMEM));
    EXPECT(counts.enters == counts.exits);
    p101_error_reset(err);

    p101_env_set_fault_injector(env, NULL, NULL);
    p101_env_set_call_observer(env, NULL, NULL);
}

static void test_short_read_fault(struct p101_error *err)
{
    struct p101_env *env;
    char             input[] = "abcd";
    char             output[sizeof(input)] = {0};
    int              fds[2];

    EXPECT(setenv("P101_FAULT_CALL", "1", 1) == 0);
    EXPECT(setenv("P101_FAULT_NAME", "read", 1) == 0);
    EXPECT(setenv("P101_FAULT_MODE", "short", 1) == 0);
    EXPECT(setenv("P101_FAULT_AMOUNT", "2", 1) == 0);
    env = p101_env_create(err, NULL);
    EXPECT(unsetenv("P101_FAULT_CALL") == 0);
    EXPECT(unsetenv("P101_FAULT_NAME") == 0);
    EXPECT(unsetenv("P101_FAULT_MODE") == 0);
    EXPECT(unsetenv("P101_FAULT_AMOUNT") == 0);
    EXPECT(env != NULL);

    if(env != NULL)
    {
        EXPECT(p101_pipe(env, err, fds) == 0);
        EXPECT(p101_write(env, err, fds[1], input, sizeof(input)) == (ssize_t)sizeof(input));
        EXPECT(p101_read(env, err, fds[0], output, sizeof(output)) == 2);
        EXPECT(memcmp(input, output, 2U) == 0);
        EXPECT(p101_close(env, err, fds[0]) == 0);
        EXPECT(p101_close(env, err, fds[1]) == 0);
        p101_env_destroy(env);
    }
}

int main(void)
{
    struct event_counts allocation_counts = {0};
    struct p101_error  *err;
    struct p101_env    *env;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }

    p101_env_set_alloc_observer(env, observe_allocations, &allocation_counts);
    test_sentinel_contracts(env, err);
    EXPECT(allocation_counts.allocations >= 1);
    p101_env_set_alloc_observer(env, NULL, NULL);
    test_eof_is_not_an_error(env, err);
    test_resource_events(env, err);
    test_regex_error_message_cleanup(env, err);
    test_expected_statuses(env, err);
    test_faults_and_balanced_trace(env, err);
    test_short_read_fault(err);

    p101_env_destroy(env);
    p101_error_destroy(err);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
