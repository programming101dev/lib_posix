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

#include "p101_posix/p101_glob.h"

int p101_glob(const struct p101_env *env, struct p101_error *err, const char *restrict pattern, int flags, int (*errfunc)(const char *epath, int eerrno), glob_t *restrict pglob)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = glob(pattern, flags, errfunc, pglob);

    if(ret_val != 0 && ret_val != GLOB_NOMATCH)
    {
        if(ret_val == GLOB_ABORTED)
        {
            P101_ERROR_RAISE_SYSTEM(err, "", ret_val);
        }
        else if(ret_val == GLOB_NOSPACE)
        {
            P101_ERROR_RAISE_SYSTEM(err, "", ret_val);
        }
        else
        {
            P101_ERROR_RAISE_SYSTEM(err, "<unknown glob error>", ret_val);
        }
    }

    return ret_val;
}

void p101_globfree(const struct p101_env *env, glob_t *pglob)
{
    P101_TRACE(env);
    errno = 0;
    globfree(pglob);
}
