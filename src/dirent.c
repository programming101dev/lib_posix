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

#include "p101_posix/p101_dirent.h"
#include "p101_posix_internal.h"

int p101_alphasort(const struct p101_env *env, const struct dirent **d1, const struct dirent **d2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = alphasort(d1, d2);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_closedir(const struct p101_env *env, struct p101_error *err, DIR *dirp)
{
    int fd;
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    fd      = dirfd(dirp);
    errno   = 0;
    ret_val = closedir(dirp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else if(fd >= 0)
    {
        P101_TRACK_CLOSE(env, fd);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_dirfd(const struct p101_env *env, struct p101_error *err, DIR *dirp)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = dirfd(dirp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

DIR *p101_fdopendir(const struct p101_env *env, struct p101_error *err, int fd)
{
    DIR *ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = fdopendir(fd);

    if(ret_val == NULL && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

DIR *p101_opendir(const struct p101_env *env, struct p101_error *err, const char *dirname)
{
    DIR *ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = opendir(dirname);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        int fd;

        fd = dirfd(ret_val);
        if(fd >= 0)
        {
            P101_TRACK_OPEN(env, fd);
        }
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

struct dirent *p101_readdir(const struct p101_env *env, struct p101_error *err, DIR *dirp)
{
    struct dirent *ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = readdir(dirp);    // cppcheck-suppress readdirCalled

    if(ret_val == NULL && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

void p101_rewinddir(const struct p101_env *env, DIR *dirp)
{
    P101_TRACE(env);
    errno = 0;
    rewinddir(dirp);
    P101_TRACE_EXIT(env);
}

/* cppcheck-suppress funcArgNamesDifferentUnnamed */
int p101_scandir(const struct p101_env *env, struct p101_error *err, const char *dir, struct dirent ***namelist, int (*sel)(const struct dirent *), int (*compar)(const struct dirent **, const struct dirent **))
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = scandir(dir, namelist, sel, compar);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        if(*namelist != NULL)
        {
            P101_TRACK_ALLOC(env, (const void *)*namelist, (size_t)ret_val * sizeof(**namelist));
            for(int index = 0; index < ret_val; index++)
            {
                P101_TRACK_ALLOC(env, (*namelist)[index], sizeof(*(*namelist)[index]));
            }
        }
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
