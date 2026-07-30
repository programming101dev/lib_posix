/*
 * Copyright 2021-2024 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "p101_posix/p101_pthread.h"
#include "p101_posix_internal.h"

enum
{
    P101_HEX_SHIFT            = 4,
    P101_HEX_MASK             = 15,
    P101_THREAD_METADATA_SIZE = 8 + (sizeof(pthread_t) * 2) + 1,
    P101_MUTEX_OWNER_ID_SIZE  = P101_ENV_POINTER_RESOURCE_ID_SIZE + P101_THREAD_METADATA_SIZE + 1
};

static void pthread_metadata(pthread_t thread, char metadata[P101_THREAD_METADATA_SIZE])
{
    static const char    digits[] = "0123456789abcdef";
    static const char    prefix[] = "thread=";
    const unsigned char *bytes;
    size_t               offset;

    bytes = (const unsigned char *)&thread;
    for(offset = 0U; offset < sizeof(prefix) - 1U; offset++)
    {
        metadata[offset] = prefix[offset];
    }
    for(size_t i = 0U; i < sizeof(pthread_t); i++)
    {
        metadata[offset++] = digits[(bytes[i] >> P101_HEX_SHIFT) & P101_HEX_MASK];
        metadata[offset++] = digits[bytes[i] & P101_HEX_MASK];
    }
    metadata[offset] = '\0';
}

static void pthread_track_held(const struct p101_env *env, p101_tool_event_resource_kind event, const char *resource_class, const void *resource, const char *file_name, const char *function_name, int line_number)
{
    char   metadata[P101_THREAD_METADATA_SIZE];
    char   pointer_id[P101_ENV_POINTER_RESOURCE_ID_SIZE];
    char   resource_id[P101_MUTEX_OWNER_ID_SIZE];
    size_t offset;

    pthread_metadata(p101_pthread_self(env), metadata);
    p101_env_pointer_resource_id(pointer_id, sizeof(pointer_id), resource);
    offset = 0U;
    while(pointer_id[offset] != '\0')
    {
        resource_id[offset] = pointer_id[offset];
        offset++;
    }
    resource_id[offset++] = '@';
    for(size_t i = 0U; metadata[i] != '\0'; i++)
    {
        resource_id[offset++] = metadata[i];
    }
    resource_id[offset] = '\0';
    p101_env_track_resource(env, event, resource_class, resource_id, NULL, 0U, metadata, file_name, function_name, line_number);
}

static void pthread_track_joinable(const struct p101_env *env, p101_tool_event_resource_kind event, pthread_t thread, const char *file_name, const char *function_name, int line_number)
{
    char resource_id[P101_THREAD_METADATA_SIZE];

    pthread_metadata(thread, resource_id);
    p101_env_track_resource(env, event, "pthread-joinable-thread", resource_id, NULL, 0U, NULL, file_name, function_name, line_number);
}

static void pthread_track_pointer_wait(const struct p101_env *env, p101_tool_event_resource_kind event, const char *resource_class, const void *resource, const char *file_name, const char *function_name, int line_number)
{
    char   metadata[P101_THREAD_METADATA_SIZE];
    char   pointer_id[P101_ENV_POINTER_RESOURCE_ID_SIZE];
    char   resource_id[P101_MUTEX_OWNER_ID_SIZE];
    size_t offset;

    pthread_metadata(p101_pthread_self(env), metadata);
    p101_env_pointer_resource_id(pointer_id, sizeof(pointer_id), resource);
    offset = 0U;
    while(pointer_id[offset] != '\0')
    {
        resource_id[offset] = pointer_id[offset];
        offset++;
    }
    resource_id[offset++] = '@';
    for(size_t i = 0U; metadata[i] != '\0'; i++)
    {
        resource_id[offset++] = metadata[i];
    }
    resource_id[offset] = '\0';
    p101_env_track_resource(env, event, resource_class, resource_id, NULL, 0U, metadata, file_name, function_name, line_number);
}

static void pthread_track_join_wait(const struct p101_env *env, p101_tool_event_resource_kind event, pthread_t target, const char *file_name, const char *function_name, int line_number)
{
    char current_id[P101_THREAD_METADATA_SIZE];
    char target_id[P101_THREAD_METADATA_SIZE];

    pthread_metadata(p101_pthread_self(env), current_id);
    pthread_metadata(target, target_id);
    p101_env_track_resource(env, event, "pthread-join-wait", current_id, target_id, 0U, current_id, file_name, function_name, line_number);
}

#define P101_PTHREAD_TRACK_MUTEX_ACQUIRE(env, mutex) pthread_track_held((env), P101_TOOL_EVENT_RESOURCE_ACQUIRE, "pthread-mutex-held", (mutex), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_MUTEX_RELEASE(env, mutex) pthread_track_held((env), P101_TOOL_EVENT_RESOURCE_RELEASE, "pthread-mutex-held", (mutex), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_RWLOCK_ACQUIRE(env, rwlock) pthread_track_held((env), P101_TOOL_EVENT_RESOURCE_ACQUIRE, "pthread-rwlock-held", (rwlock), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_RWLOCK_RELEASE(env, rwlock) pthread_track_held((env), P101_TOOL_EVENT_RESOURCE_RELEASE, "pthread-rwlock-held", (rwlock), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOINABLE_ACQUIRE(env, thread) pthread_track_joinable((env), P101_TOOL_EVENT_RESOURCE_ACQUIRE, (thread), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOINABLE_RELEASE(env, thread) pthread_track_joinable((env), P101_TOOL_EVENT_RESOURCE_RELEASE, (thread), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, resource_class, resource) pthread_track_pointer_wait((env), P101_TOOL_EVENT_RESOURCE_ACQUIRE, (resource_class), (resource), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_WAIT_RELEASE(env, resource_class, resource) pthread_track_pointer_wait((env), P101_TOOL_EVENT_RESOURCE_RELEASE, (resource_class), (resource), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOIN_WAIT_ACQUIRE(env, thread) pthread_track_join_wait((env), P101_TOOL_EVENT_RESOURCE_ACQUIRE, (thread), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOIN_WAIT_RELEASE(env, thread) pthread_track_join_wait((env), P101_TOOL_EVENT_RESOURCE_RELEASE, (thread), __FILE__, __func__, __LINE__)

/* cppcheck-suppress funcArgNamesDifferentUnnamed */
int p101_pthread_atfork(const struct p101_env *env, struct p101_error *err, void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_atfork(prepare, parent, child);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_destroy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_destroy(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-attributes", attr, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getdetachstate(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *attr, int *detachstate)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_getdetachstate(attr, detachstate);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getguardsize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict guardsize)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_getguardsize(attr, guardsize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getschedparam(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, struct sched_param *restrict param)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_getschedparam(attr, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_init(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_init(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-attributes", attr, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setdetachstate(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int detachstate)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_setdetachstate(attr, detachstate);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setguardsize(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, size_t guardsize)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_setguardsize(attr, guardsize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_attr_t *restrict attr, const struct sched_param *restrict param)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_attr_setschedparam(attr, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cancel(const struct p101_env *env, struct p101_error *err, pthread_t thread)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_cancel(thread);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cond_broadcast(const struct p101_env *env, struct p101_error *err, pthread_cond_t *cond)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_cond_broadcast(cond);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cond_destroy(const struct p101_env *env, struct p101_error *err, pthread_cond_t *cond)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_cond_destroy(cond);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-condition", cond, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cond_init(const struct p101_env *env, struct p101_error *err, pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_cond_init(cond, attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-condition", cond, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cond_signal(const struct p101_env *env, struct p101_error *err, pthread_cond_t *cond)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_cond_signal(cond);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cond_timedwait(const struct p101_env *env, struct p101_error *err, pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_MUTEX_RELEASE(env, mutex);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-condition-wait", cond);
    errno   = 0;
    ret_val = pthread_cond_timedwait(cond, mutex, abstime);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-condition-wait", cond);
    P101_PTHREAD_TRACK_MUTEX_ACQUIRE(env, mutex);

    if(ret_val != 0 && ret_val != ETIMEDOUT)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_cond_wait(const struct p101_env *env, struct p101_error *err, pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_MUTEX_RELEASE(env, mutex);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-condition-wait", cond);
    errno   = 0;
    ret_val = pthread_cond_wait(cond, mutex);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-condition-wait", cond);
    P101_PTHREAD_TRACK_MUTEX_ACQUIRE(env, mutex);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_condattr_destroy(const struct p101_env *env, struct p101_error *err, pthread_condattr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_condattr_destroy(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-condition-attributes", attr, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_condattr_init(const struct p101_env *env, struct p101_error *err, pthread_condattr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_condattr_init(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-condition-attributes", attr, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

/* cppcheck-suppress funcArgNamesDifferentUnnamed */
int p101_pthread_create(const struct p101_env *env, struct p101_error *err, pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg)
{
    int detach_state;
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    detach_state = PTHREAD_CREATE_JOINABLE;
    if(attr != NULL)
    {
        ret_val = pthread_attr_getdetachstate(attr, &detach_state);
        if(ret_val != 0)
        {
            P101_ERROR_RAISE_ERRNO(err, ret_val);
            P101_TRACE_EXIT(env);
            return ret_val;
        }
    }
    errno   = 0;
    ret_val = pthread_create(thread, attr, start_routine, arg);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else if(detach_state == PTHREAD_CREATE_JOINABLE)
    {
        P101_PTHREAD_TRACK_JOINABLE_ACQUIRE(env, *thread);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_detach(const struct p101_env *env, struct p101_error *err, pthread_t thread)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_detach(thread);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_JOINABLE_RELEASE(env, thread);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_equal(const struct p101_env *env, pthread_t t1, pthread_t t2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pthread_equal(t1, t2);

    P101_TRACE_EXIT(env);
    return ret_val;
}

void p101_pthread_exit(const struct p101_env *env, void *value_ptr)
{
    P101_TRACE(env);
    errno = 0;
    P101_TRACE_EXIT(env);
    pthread_exit(value_ptr);
}

void *p101_pthread_getspecific(const struct p101_env *env, pthread_key_t key)
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pthread_getspecific(key);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_join(const struct p101_env *env, struct p101_error *err, pthread_t thread, void **value_ptr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_JOIN_WAIT_ACQUIRE(env, thread);
    errno   = 0;
    ret_val = pthread_join(thread, value_ptr);
    P101_PTHREAD_TRACK_JOIN_WAIT_RELEASE(env, thread);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_JOINABLE_RELEASE(env, thread);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_key_create(const struct p101_env *env, struct p101_error *err, pthread_key_t *key, void (*destructor)(void *))
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_key_create(key, destructor);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_key_delete(const struct p101_env *env, struct p101_error *err, pthread_key_t key)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_key_delete(key);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutex_destroy(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutex_destroy(mutex);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-mutex", mutex, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutex_init(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutex_init(mutex, attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-mutex", mutex, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutex_lock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-mutex-wait", mutex);
    errno   = 0;
    ret_val = pthread_mutex_lock(mutex);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-mutex-wait", mutex);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_MUTEX_ACQUIRE(env, mutex);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutex_trylock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-mutex-wait", mutex);
    errno   = 0;
    ret_val = pthread_mutex_trylock(mutex);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-mutex-wait", mutex);

    if(ret_val != 0 && ret_val != EBUSY)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else if(ret_val == 0)
    {
        P101_PTHREAD_TRACK_MUTEX_ACQUIRE(env, mutex);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutex_unlock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutex_unlock(mutex);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_MUTEX_RELEASE(env, mutex);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutexattr_destroy(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutexattr_destroy(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-mutex-attributes", attr, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutexattr_gettype(const struct p101_env *env, struct p101_error *err, const pthread_mutexattr_t *restrict attr, int *restrict type)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutexattr_gettype(attr, type);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutexattr_init(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutexattr_init(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-mutex-attributes", attr, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutexattr_settype(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr, int type)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutexattr_settype(attr, type);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_once(const struct p101_env *env, struct p101_error *err, pthread_once_t *once_control, void (*init_routine)(void))
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_once(once_control, init_routine);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_destroy(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlock_destroy(rwlock);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-rwlock", rwlock, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_init(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlock_init(rwlock, attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-rwlock", rwlock, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_rdlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-rwlock-read-wait", rwlock);
    errno   = 0;
    ret_val = pthread_rwlock_rdlock(rwlock);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-rwlock-read-wait", rwlock);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_RWLOCK_ACQUIRE(env, rwlock);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_tryrdlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-rwlock-read-wait", rwlock);
    errno   = 0;
    ret_val = pthread_rwlock_tryrdlock(rwlock);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-rwlock-read-wait", rwlock);

    if(ret_val != 0 && ret_val != EBUSY)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else if(ret_val == 0)
    {
        P101_PTHREAD_TRACK_RWLOCK_ACQUIRE(env, rwlock);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_trywrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-rwlock-write-wait", rwlock);
    errno   = 0;
    ret_val = pthread_rwlock_trywrlock(rwlock);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-rwlock-write-wait", rwlock);

    if(ret_val != 0 && ret_val != EBUSY)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else if(ret_val == 0)
    {
        P101_PTHREAD_TRACK_RWLOCK_ACQUIRE(env, rwlock);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_unlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlock_unlock(rwlock);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_RWLOCK_RELEASE(env, rwlock);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_wrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    P101_PTHREAD_TRACK_WAIT_ACQUIRE(env, "pthread-rwlock-write-wait", rwlock);
    errno   = 0;
    ret_val = pthread_rwlock_wrlock(rwlock);
    P101_PTHREAD_TRACK_WAIT_RELEASE(env, "pthread-rwlock-write-wait", rwlock);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_RWLOCK_ACQUIRE(env, rwlock);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlockattr_destroy(const struct p101_env *env, struct p101_error *err, pthread_rwlockattr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlockattr_destroy(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_RELEASE(env, "pthread-rwlock-attributes", attr, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlockattr_init(const struct p101_env *env, struct p101_error *err, pthread_rwlockattr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlockattr_init(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_POSIX_TRACK_POINTER_ACQUIRE(env, "pthread-rwlock-attributes", attr, 0U, NULL);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

pthread_t p101_pthread_self(const struct p101_env *env)
{
    pthread_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pthread_self();

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_setcancelstate(const struct p101_env *env, struct p101_error *err, int state, int *oldstate)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_setcancelstate(state, oldstate);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_setcanceltype(const struct p101_env *env, struct p101_error *err, int type, int *oldtype)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_setcanceltype(type, oldtype);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_setspecific(const struct p101_env *env, struct p101_error *err, pthread_key_t key, const void *value)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_setspecific(key, value);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

void p101_pthread_testcancel(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    pthread_testcancel();
    P101_TRACE_EXIT(env);
}
