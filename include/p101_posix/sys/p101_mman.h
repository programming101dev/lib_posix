#ifndef LIBP101_POSIX_SYS_P101_MMAN_H
#define LIBP101_POSIX_SYS_P101_MMAN_H

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
#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void *p101_mmap(const struct p101_env *env, struct p101_error *err, void *addr, size_t len, int prot, int flags, int fildes, off_t off);
    int   p101_mprotect(const struct p101_env *env, struct p101_error *err, void *addr, size_t len, int prot);
    int   p101_munmap(const struct p101_env *env, struct p101_error *err, void *addr, size_t len);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_SYS_P101_MMAN_H
