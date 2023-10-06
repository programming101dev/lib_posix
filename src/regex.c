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

#include "p101_posix/p101_regex.h"
#include <p101_c/p101_stdlib.h>

int p101_regcomp(const struct p101_env *env, struct p101_error *err, regex_t *restrict preg, const char *restrict pattern, int cflags)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = regcomp(preg, pattern, cflags);

    if(ret_val != 0)
    {
        size_t len;
        char  *msg;

        len = p101_regerror(env, ret_val, preg, NULL, 0);
        msg = (char *)p101_malloc(env, err, len);

        if(p101_error_has_no_error(err))
        {
            // TODO: this needs to be fixed - remove the NOLINT

#ifndef __clang_analyzer__
            // cppcheck-suppress unreadVariable
            len = p101_regerror(env, ret_val, preg, msg, len);    // NOLINT(clang-analyzer-deadcode.DeadStores)
#endif
            P101_ERROR_RAISE_SYSTEM(err, msg, ret_val);
            p101_free(env, msg);
        }
    }

    return ret_val;
}

size_t p101_regerror(const struct p101_env *env, int errcode, const regex_t *restrict preg, char *restrict errbuf, size_t errbuf_size)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = regerror(errcode, preg, errbuf, errbuf_size);

    return ret_val;
}

int p101_regexec(const struct p101_env *env, const regex_t *restrict preg, const char *restrict string, size_t nmatch, regmatch_t pmatch[restrict], int eflags)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = regexec(preg, string, nmatch, pmatch, eflags);

    return ret_val;
}

void p101_regfree(const struct p101_env *env, regex_t *preg)
{
    P101_TRACE(env);
    errno = 0;
    regfree(preg);
}
