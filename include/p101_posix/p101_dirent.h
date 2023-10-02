#ifndef LIBP101_POSIX_P101_DIRENT_H
#define LIBP101_POSIX_P101_DIRENT_H

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

#include <dirent.h>
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int            p101_alphasort(const struct p101_env *env, struct p101_error *err, const struct dirent **d1, const struct dirent **d2);
    int            p101_closedir(const struct p101_env *env, struct p101_error *err, DIR *dirp);
    int            p101_dirfd(const struct p101_env *env, struct p101_error *err, DIR *dirp);
    DIR           *p101_fdopendir(const struct p101_env *env, struct p101_error *err, int fd);
    DIR           *p101_opendir(const struct p101_env *env, struct p101_error *err, const char *dirname);
    struct dirent *p101_readdir(const struct p101_env *env, struct p101_error *err, DIR *dirp);
    void           p101_rewinddir(const struct p101_env *env, DIR *dirp);
    int            p101_scandir(const struct p101_env *env, struct p101_error *err, const char *dir, struct dirent ***namelist, int (*sel)(const struct dirent *),
                                int (*compar)(const struct dirent **, const struct dirent **));

#ifdef __cplusplus
}
#endif

// obsolete
// int p101_readdir_r(const struct p101_env *env, struct p101_error *err, DIR *restrict dirp, struct dirent *restrict entry, struct dirent **restrict result);

#endif    // LIBP101_POSIX_P101_DIRENT_H
