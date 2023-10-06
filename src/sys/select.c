/*
 * Copyright 2021-2022 D'Arcy Smith.
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

#include "p101_posix/sys/p101_select.h"

int p101_pselect(const struct p101_env *env, struct p101_error *err, int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, const struct timespec *restrict timeout, const sigset_t *restrict sigmask)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pselect(nfds, readfds, writefds, errorfds, timeout, sigmask);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_select(const struct p101_env *env, struct p101_error *err, int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = select(nfds, readfds, writefds, errorfds, timeout);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
