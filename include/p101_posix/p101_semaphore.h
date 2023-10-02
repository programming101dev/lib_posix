#ifndef LIBP101_POSIX_P101_SEMAPHPORE_H
#define LIBP101_POSIX_P101_SEMAPHPORE_H

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
#include <semaphore.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int    p101_sem_close(const struct p101_env *env, struct p101_error *err, sem_t *sem);
    sem_t *p101_sem_open(const struct p101_env *env, struct p101_error *err, const char *name, int oflag, ...);
    int    p101_sem_post(const struct p101_env *env, struct p101_error *err, sem_t *sem);
    int    p101_sem_trywait(const struct p101_env *env, struct p101_error *err, sem_t *sem);
    int    p101_sem_unlink(const struct p101_env *env, struct p101_error *err, const char *name);
    int    p101_sem_wait(const struct p101_env *env, struct p101_error *err, sem_t *sem);

#ifdef __cplusplus
}
#endif

// not on macOS
// int p101_sem_timedwait(const struct p101_env *env, struct p101_error *err, sem_t *restrict sem, const struct timespec *restrict abstime);

// deprecated on macOS
// int p101_sem_destroy(const struct p101_env *env, struct p101_error *err, sem_t *sem);
// int p101_sem_getvalue(const struct p101_env *env, struct p101_error *err, sem_t *restrict sem, int *restrict sval);
// int p101_sem_init(const struct p101_env *env, struct p101_error *err, sem_t *sem, int pshared, unsigned value);

#endif    // LIBP101_POSIX_P101_SEMAPHPORE_H
