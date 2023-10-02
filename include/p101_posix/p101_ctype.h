#ifndef LIBP101_POSIX_P101_CTYPE_H
#define LIBP101_POSIX_P101_CTYPE_H

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

#include <p101_env/env.h>

#if(defined __APPLE__) || (defined __FreeBSD__)
    #include <xlocale.h>
#else
    #include <locale.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    int p101_isalnum_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isalpha_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isblank_l(const struct p101_env *env, int c, locale_t locale);
    int p101_iscntrl_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isdigit_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isgraph_l(const struct p101_env *env, int c, locale_t locale);
    int p101_islower_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isprint_l(const struct p101_env *env, int c, locale_t locale);
    int p101_ispunct_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isspace_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isupper_l(const struct p101_env *env, int c, locale_t locale);
    int p101_isxdigit_l(const struct p101_env *env, int c, locale_t locale);
    int p101_tolower_l(const struct p101_env *env, int c, locale_t locale);
    int p101_toupper_l(const struct p101_env *env, int c, locale_t locale);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_CTYPE_H
