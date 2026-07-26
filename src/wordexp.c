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

#include "p101_posix/p101_wordexp.h"

static const char *wordexp_error_message(int err_code);

static const char *wordexp_error_message(int err_code)
{
    const char *msg;

    switch(err_code)
    {
        case WRDE_BADCHAR:
            msg = "Illegal character in word expansion";
            break;
        case WRDE_BADVAL:
            msg = "Undefined shell variable in word expansion";
            break;
        case WRDE_CMDSUB:
            msg = "Command substitution requested in word expansion";
            break;
        case WRDE_NOSPACE:
            msg = "Out of memory during word expansion";
            break;
        case WRDE_SYNTAX:
            msg = "Shell syntax error in word expansion";
            break;
        default:
            msg = "Unknown word expansion error";
            break;
    }

    return msg;
}

int p101_wordexp(const struct p101_env *env, struct p101_error *err, const char *restrict words, wordexp_t *restrict pwordexp, int flags)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wordexp(words, pwordexp, flags);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_SYSTEM(err, wordexp_error_message(ret_val), ret_val);
    }

    return ret_val;
}

void p101_wordfree(const struct p101_env *env, wordexp_t *pwordexp)
{
    P101_TRACE(env);
    errno = 0;
    wordfree(pwordexp);
}
