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

#include "p101_posix/p101_ctype.h"
#include <ctype.h>

int p101_isalnum_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isalnum_l(c, locale);

    return ret_val;
}

int p101_isalpha_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isalpha_l(c, locale);

    return ret_val;
}

int p101_isblank_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isblank_l(c, locale);

    return ret_val;
}

int p101_iscntrl_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iscntrl_l(c, locale);

    return ret_val;
}

int p101_isdigit_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isdigit_l(c, locale);

    return ret_val;
}

int p101_isgraph_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isgraph_l(c, locale);

    return ret_val;
}

int p101_islower_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = islower_l(c, locale);

    return ret_val;
}

int p101_isprint_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isprint_l(c, locale);

    return ret_val;
}

int p101_ispunct_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ispunct_l(c, locale);

    return ret_val;
}

int p101_isspace_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isspace_l(c, locale);

    return ret_val;
}

int p101_isupper_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isupper_l(c, locale);

    return ret_val;
}

int p101_isxdigit_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isxdigit_l(c, locale);

    return ret_val;
}

int p101_tolower_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tolower_l(c, locale);

    return ret_val;
}

int p101_toupper_l(const struct p101_env *env, int c, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = toupper_l(c, locale);

    return ret_val;
}
