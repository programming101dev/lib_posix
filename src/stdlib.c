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

#include "p101_posix/p101_stdlib.h"
#include <stdlib.h>

#ifdef __APPLE__
    #include <unistd.h>
#endif

int p101_getsubopt(const struct p101_env *env, struct p101_error *err, char **optionp, char *const *keylistp, char **valuep)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getsubopt(optionp, keylistp, valuep);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

char *p101_mkdtemp(const struct p101_env *env, struct p101_error *err, char *name_template)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = mkdtemp(name_template);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_mkstemp(const struct p101_env *env, struct p101_error *err, char *name_template)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = mkstemp(name_template);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setenv(const struct p101_env *env, struct p101_error *err, const char *envname, const char *envval, int overwrite)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setenv(envname, envval, overwrite);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_unsetenv(const struct p101_env *env, struct p101_error *err, const char *name)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = unsetenv(name);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
