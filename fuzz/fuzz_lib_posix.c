/*
 * Parser/conversion fuzz harness for lib_posix. Commands are disabled in
 * wordexp, and inputs are bounded before they reach the wrappers.
 */
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_posix/arpa/p101_inet.h>
#include <p101_posix/p101_fnmatch.h>
#include <p101_posix/p101_regex.h>
#include <p101_posix/p101_wchar.h>
#include <p101_posix/p101_wordexp.h>
#include <regex.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wordexp.h>

enum
{
    MAX_FUZZ_TEXT = 4096
};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    struct p101_error *err;
    struct p101_env   *env;
    const char        *source;
    mbstate_t          state = {0};
    regex_t            regex;
    wordexp_t          words = {0};
    wchar_t            wide[MAX_FUZZ_TEXT + 1];
    unsigned char      address[16];
    char               text[MAX_FUZZ_TEXT + 1];
    int                regex_status;
    int                word_status;

    if(size > MAX_FUZZ_TEXT)
    {
        return 0;
    }

    memcpy(text, data, size);
    text[size] = '\0';
    err        = p101_error_create(false);
    if(err == NULL)
    {
        return 0;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return 0;
    }

    (void)p101_fnmatch(env, err, text, text, 0);
    p101_error_reset(err);

    regex_status = p101_regcomp(env, err, &regex, text, REG_EXTENDED);
    if(regex_status == 0)
    {
        (void)p101_regexec(env, &regex, text, 0, NULL, 0);
        p101_regfree(env, &regex);
    }
    p101_error_reset(err);

    word_status = p101_wordexp(env, err, text, &words, WRDE_NOCMD);
    if(word_status == 0)
    {
        p101_wordfree(env, &words);
    }
    p101_error_reset(err);

    source = text;
    (void)p101_mbsnrtowcs(env, err, wide, &source, size, MAX_FUZZ_TEXT, &state);
    p101_error_reset(err);

    (void)p101_inet_pton(env, err, AF_INET, text, address);
    p101_error_reset(err);
    (void)p101_inet_pton(env, err, AF_INET6, text, address);

    p101_env_destroy(env);
    p101_error_destroy(err);
    return 0;
}
