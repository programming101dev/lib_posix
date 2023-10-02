#ifndef LIBP101_POSIX_P101_AIO_H
#define LIBP101_POSIX_P101_AIO_H

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

#include <aio.h>
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int     p101_aio_cancel(const struct p101_env *env, struct p101_error *err, int fildes, struct aiocb *aiocbp);
    int     p101_aio_error(const struct p101_env *env, struct p101_error *err, const struct aiocb *aiocbp);
    int     p101_aio_read(const struct p101_env *env, struct p101_error *err, struct aiocb *aiocbp);
    ssize_t p101_aio_return(const struct p101_env *env, struct p101_error *err, struct aiocb *aiocbp);
    int     p101_aio_suspend(const struct p101_env *env, struct p101_error *err, const struct aiocb *const list[], int nent, const struct timespec *timeout);
    int     p101_aio_write(const struct p101_env *env, struct p101_error *err, struct aiocb *aiocbp);
    int     p101_lio_listio(const struct p101_env *env, struct p101_error *err, int mode, struct aiocb *restrict const list[restrict], int nent, struct sigevent *restrict sig);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_AIO_H
