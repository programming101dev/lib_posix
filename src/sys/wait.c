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

#include "p101_posix/sys/p101_wait.h"

pid_t p101_wait(const struct p101_env *env, struct p101_error *err, int *stat_loc)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wait(stat_loc);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_waitid(const struct p101_env *env, struct p101_error *err, idtype_t idtype, id_t id, siginfo_t *infop, int options)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = waitid(idtype, id, infop, options);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

pid_t p101_waitpid(const struct p101_env *env, struct p101_error *err, pid_t pid, int *stat_loc, int options)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = waitpid(pid, stat_loc, options);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
