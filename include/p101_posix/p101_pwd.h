#ifndef LIBP101_POSIX_P101_PWD_H
#define LIBP101_POSIX_P101_PWD_H

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
#include <pwd.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int p101_getpwnam_r(const struct p101_env *env, struct p101_error *err, const char *name, struct passwd *pwd, char *buffer, size_t bufsize, struct passwd **result);
    int p101_getpwuid_r(const struct p101_env *env, struct p101_error *err, uid_t uid, struct passwd *pwd, char *buffer, size_t bufsize, struct passwd **result);

#ifdef __cplusplus
}
#endif

// unsafe
// struct passwd *p101_getpwnam(const struct p101_env *env, struct p101_error *err, const char *name);
// struct passwd *p101_getpwuid(const struct p101_env *env, struct p101_error *err, uid_t uid);

#endif    // LIBP101_POSIX_P101_PWD_H
