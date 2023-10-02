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

#include "p101_posix/p101_fcntl.h"
#include <fcntl.h>

int p101_creat(const struct p101_env *env, struct p101_error *err, const char *path, mode_t mode)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = creat(path, mode);    // NOLINT(android-cloexec-creat)

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_fcntl(const struct p101_env *env, struct p101_error *err, int fildes, int cmd, ...)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    // TODO: fix the ... or delete the function
    ret_val = fcntl(fildes, cmd, 0);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_open(const struct p101_env *env, struct p101_error *err, const char *path, int oflag, ...)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    // TODO: fix the ...
    ret_val = open(path, oflag, 0);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_openat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int oflag, ...)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    // TODO: fix the ...
    ret_val = openat(fd, path, oflag, 0);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
