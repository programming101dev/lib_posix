#ifndef LIBP101_POSIX_P101_SEMAPHPORE_H
#define LIBP101_POSIX_P101_SEMAPHPORE_H

/*
 * Copyright 2022-2024 D'Arcy Smith.
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

#ifndef P101_ATTR_WARN_UNUSED_RESULT
    #if defined(__GNUC__) || defined(__clang__)
        #define P101_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
    #else
        #define P101_ATTR_WARN_UNUSED_RESULT
    #endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    int    p101_sem_close(const struct p101_env *env, struct p101_error *err, sem_t *sem);
    sem_t *p101_sem_open(const struct p101_env *env, struct p101_error *err, const char *name, int oflag, ...) P101_ATTR_WARN_UNUSED_RESULT;
    int    p101_sem_post(const struct p101_env *env, struct p101_error *err, sem_t *sem);
    int    p101_sem_trywait(const struct p101_env *env, struct p101_error *err, sem_t *sem);
    int    p101_sem_unlink(const struct p101_env *env, struct p101_error *err, const char *name);
    int    p101_sem_wait(const struct p101_env *env, struct p101_error *err, sem_t *sem);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_SEMAPHORE_H
