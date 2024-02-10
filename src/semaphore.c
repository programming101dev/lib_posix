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

#include "p101_posix/p101_semaphore.h"

int p101_sem_close(const struct p101_env *env, struct p101_error *err, sem_t *sem)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sem_close(sem);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

sem_t *p101_sem_open(const struct p101_env *env, struct p101_error *err, const char *name, int oflag, ...)
{
    sem_t *ret_val;

    P101_TRACE(env);
    errno = 0;
    // TODO: fix the ... or remove the function
    ret_val = sem_open(name, oflag, 0);

    if(ret_val == SEM_FAILED)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_sem_post(const struct p101_env *env, struct p101_error *err, sem_t *sem)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sem_post(sem);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_sem_trywait(const struct p101_env *env, struct p101_error *err, sem_t *sem)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sem_trywait(sem);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_sem_unlink(const struct p101_env *env, struct p101_error *err, const char *name)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sem_unlink(name);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_sem_wait(const struct p101_env *env, struct p101_error *err, sem_t *sem)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sem_wait(sem);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
