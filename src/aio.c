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

#include "p101_posix/p101_aio.h"

int p101_aio_cancel(const struct p101_env *env, struct p101_error *err, int fildes, struct aiocb *aiocbp)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = aio_cancel(fildes, aiocbp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_aio_error(const struct p101_env *env, struct p101_error *err, const struct aiocb *aiocbp)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = aio_error(aiocbp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_aio_read(const struct p101_env *env, struct p101_error *err, struct aiocb *aiocbp)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = aio_read(aiocbp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_aio_return(const struct p101_env *env, struct p101_error *err, struct aiocb *aiocbp)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = aio_return(aiocbp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_aio_suspend(const struct p101_env *env, struct p101_error *err, const struct aiocb *const list[], int nent, const struct timespec *timeout)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = aio_suspend(list, nent, timeout);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_aio_write(const struct p101_env *env, struct p101_error *err, struct aiocb *aiocbp)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = aio_write(aiocbp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_lio_listio(const struct p101_env *env, struct p101_error *err, int mode, struct aiocb *restrict const list[restrict], int nent, struct sigevent *restrict sig)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#endif
    ret_val = lio_listio(mode, list, nent, sig);
#pragma GCC diagnostic pop

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
