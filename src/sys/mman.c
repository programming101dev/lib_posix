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

#include "p101_posix/sys/p101_mman.h"
#include <sys/mman.h>

void *p101_mmap(const struct p101_env *env, struct p101_error *err, void *addr, size_t len, int prot, int flags, int fildes, off_t off)    // cppcheck-suppress constParameterPointer
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = mmap(addr, len, prot, flags, fildes, off);

    if(ret_val == MAP_FAILED)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_mprotect(const struct p101_env *env, struct p101_error *err, void *addr, size_t len, int prot)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = mprotect(addr, len, prot);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_munmap(const struct p101_env *env, struct p101_error *err, void *addr, size_t len)    // cppcheck-suppress constParameterPointer
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = munmap(addr, len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
