#ifndef LIBP101_POSIX_P101_STDLIB_H
#define LIBP101_POSIX_P101_STDLIB_H

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

#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int   p101_getsubopt(const struct p101_env *env, struct p101_error *err, char **optionp, char *const *keylistp, char **valuep);
    char *p101_mkdtemp(const struct p101_env *env, struct p101_error *err, char *name_template);
    int   p101_mkstemp(const struct p101_env *env, struct p101_error *err, char *name_template);
    int   p101_setenv(const struct p101_env *env, struct p101_error *err, const char *envname, const char *envval, int overwrite);
    int   p101_unsetenv(const struct p101_env *env, struct p101_error *err, const char *name);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_STDLIB_H
