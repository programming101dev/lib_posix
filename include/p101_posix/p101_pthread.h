#ifndef LIBP101_POSIX_P101_PTHREAD_H
#define LIBP101_POSIX_P101_PTHREAD_H

/*
 * Copyright 2022-2022 D'Arcy Smith.
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

#include <p101_env/env.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int p101_pthread_atfork(const struct p101_env *env, struct p101_error *err, void (*prepare)(void), void (*parent)(void), void (*child)(void));
    int p101_pthread_attr_destroy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr);
    int p101_pthread_attr_getdetachstate(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *attr, int *detachstate);
    int p101_pthread_attr_getguardsize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict guardsize);
    int p101_pthread_attr_getschedparam(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, struct sched_param *restrict param);
    int p101_pthread_attr_init(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr);
    int p101_pthread_attr_setdetachstate(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int detachstate);
    int p101_pthread_attr_setguardsize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t guardsize);
    int p101_pthread_attr_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_attr_t *restrict attr, const struct sched_param *restrict param);
    int p101_pthread_cancel(const struct p101_env *env, struct p101_error *err, pthread_t thread);
    int p101_pthread_cond_broadcast(const struct p101_env *env, struct p101_error *err, pthread_cond_t *cond);
    int p101_pthread_cond_destroy(const struct p101_env *env, struct p101_error *err, pthread_cond_t *cond);
    int p101_pthread_cond_init(const struct p101_env *env, struct p101_error *err, pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
    int p101_pthread_cond_signal(const struct p101_env *env, struct p101_error *err, pthread_cond_t *cond);
    int p101_pthread_cond_timedwait(const struct p101_env *env, struct p101_error *err, pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex,
                                    const struct timespec *restrict abstime);
    int p101_pthread_cond_wait(const struct p101_env *env, struct p101_error *err, pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
    int p101_pthread_condattr_destroy(const struct p101_env *env, struct p101_error *err, pthread_condattr_t *attr);
    int p101_pthread_condattr_init(const struct p101_env *env, struct p101_error *err, pthread_condattr_t *attr);
    int p101_pthread_create(const struct p101_env *env, struct p101_error *err, pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *),
                            void *restrict arg);
    int p101_pthread_detach(const struct p101_env *env, struct p101_error *err, pthread_t thread);
    int p101_pthread_equal(const struct p101_env *env, pthread_t t1, pthread_t t2);
    _Noreturn void p101_pthread_exit(const struct p101_env *env, void *value_ptr);
    void          *p101_pthread_getspecific(const struct p101_env *env, pthread_key_t key);
    int            p101_pthread_join(const struct p101_env *env, struct p101_error *err, pthread_t thread, void **value_ptr);
    int            p101_pthread_key_create(const struct p101_env *env, struct p101_error *err, pthread_key_t *key, void (*destructor)(void *));
    int            p101_pthread_key_delete(const struct p101_env *env, struct p101_error *err, pthread_key_t key);
    int            p101_pthread_mutex_destroy(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex);
    int            p101_pthread_mutex_init(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
    int            p101_pthread_mutex_lock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex);
    int            p101_pthread_mutex_trylock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex);
    int            p101_pthread_mutex_unlock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex);
    int            p101_pthread_mutexattr_destroy(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr);
    int            p101_pthread_mutexattr_gettype(const struct p101_env *env, struct p101_error *err, const pthread_mutexattr_t *restrict attr, int *restrict type);
    int            p101_pthread_mutexattr_init(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr);
    int            p101_pthread_mutexattr_settype(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr, int type);
    int            p101_pthread_once(const struct p101_env *env, struct p101_error *err, pthread_once_t *once_control, void (*init_routine)(void));
    int            p101_pthread_rwlock_destroy(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock);
    int            p101_pthread_rwlock_init(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
    int            p101_pthread_rwlock_rdlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock);
    int            p101_pthread_rwlock_tryrdlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock);
    int            p101_pthread_rwlock_trywrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock);
    int            p101_pthread_rwlock_unlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock);
    int            p101_pthread_rwlock_wrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *rwlock);
    int            p101_pthread_rwlockattr_destroy(const struct p101_env *env, struct p101_error *err, pthread_rwlockattr_t *attr);
    int            p101_pthread_rwlockattr_init(const struct p101_env *env, struct p101_error *err, pthread_rwlockattr_t *attr);
    pthread_t      p101_pthread_self(const struct p101_env *env);
    int            p101_pthread_setcancelstate(const struct p101_env *env, struct p101_error *err, int state, int *oldstate);
    int            p101_pthread_setcanceltype(const struct p101_env *env, struct p101_error *err, int type, int *oldtype);
    int            p101_pthread_setspecific(const struct p101_env *env, struct p101_error *err, pthread_key_t key, const void *value);
    void           p101_pthread_testcancel(const struct p101_env *env);

#ifdef __cplusplus
}
#endif

// not on macOS
// int p101_pthread_barrier_destroy(const struct p101_env *env, struct p101_error *err, pthread_barrier_t *barrier);
// int p101_pthread_barrier_init(const struct p101_env *env, struct p101_error *err, pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned
// count); int p101_pthread_barrier_wait(const struct p101_env *env, struct p101_error *err, pthread_barrier_t *barrier); int p101_pthread_barrierattr_destroy(const struct p101_env
// *env, struct p101_error *err, pthread_barrierattr_t *attr); int p101_pthread_barrierattr_init(const struct p101_env *env, struct p101_error *err, pthread_barrierattr_t *attr);
// int p101_pthread_spin_destroy(const struct p101_env *env, struct p101_error *err, pthread_spinlock_t *lock);
// int p101_pthread_spin_init(const struct p101_env *env, struct p101_error *err, pthread_spinlock_t *lock, int pshared);
// int p101_pthread_spin_lock(const struct p101_env *env, struct p101_error *err, pthread_spinlock_t *lock);
// int p101_pthread_spin_trylock(const struct p101_env *env, struct p101_error *err, pthread_spinlock_t *lock);
// int p101_pthread_spin_unlock(const struct p101_env *env, struct p101_error *err, pthread_spinlock_t *lock);
// int p101_pthread_mutex_timedlock(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
// int p101_pthread_mutex_consistent(const struct p101_env *env, struct p101_error *err, pthread_mutex_t *mutex);
// int p101_pthread_mutexattr_getrobust(const struct p101_env *env, struct p101_error *err, const pthread_mutexattr_t *restrict attr, int *restrict robust);
// int p101_pthread_mutexattr_setrobust(const struct p101_env *env, struct p101_error *err, pthread_mutexattr_t *attr, int robust);
// int p101_pthread_condattr_setclock(const struct p101_env *env, struct p101_error *err, pthread_condattr_t *attr, clockid_t clock_id);
// int p101_pthread_condattr_getclock(const struct p101_env *env, struct p101_error *err, const pthread_condattr_t *restrict attr, clockid_t *restrict clock_id);
// int p101_pthread_rwlock_timedrdlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *restrict rwlock, const struct timespec *restrict abstime);
// int p101_pthread_rwlock_timedwrlock(const struct p101_env *env, struct p101_error *err, pthread_rwlock_t *restrict rwlock, const struct timespec *restrict abstime);

#endif    // LIBP101_POSIX_P101_PTHREAD_H
