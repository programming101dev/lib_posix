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
    errno   = 0;
    ret_val = pthread_cond_timedwait(cond, mutex, abstime);

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
    errno   = 0;
    ret_val = pthread_cond_wait(cond, mutex);

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
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_create(thread, attr, start_routine, arg);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
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
    errno   = 0;
    ret_val = pthread_join(thread, value_ptr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
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
    errno   = 0;
    ret_val = pthread_mutex_lock(mutex);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_mutex_trylock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_mutex_trylock(mutex);

    if(ret_val != 0 && ret_val != EBUSY)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
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
    errno   = 0;
    ret_val = pthread_rwlock_rdlock(rwlock);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_tryrdlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlock_tryrdlock(rwlock);

    if(ret_val != 0 && ret_val != EBUSY)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_trywrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlock_trywrlock(rwlock);

    if(ret_val != 0 && ret_val != EBUSY)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
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

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_rwlock_wrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = pthread_rwlock_wrlock(rwlock);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
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
