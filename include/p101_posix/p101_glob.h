#ifndef LIBP101_POSIX_P101_GLOB_H
#define LIBP101_POSIX_P101_GLOB_H

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

#include <glob.h>
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int  p101_glob(const struct p101_env *env, struct p101_error *err, const char *restrict pattern, int flags, int (*errfunc)(const char *epath, int eerrno), glob_t *restrict pglob);
    void p101_globfree(const struct p101_env *env, glob_t *pglob);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_GLOB_H
