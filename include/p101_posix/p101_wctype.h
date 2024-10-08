#ifndef LIBP101_POSIX_P101_WCTYPE_H
#define LIBP101_POSIX_P101_WCTYPE_H

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
#include <wctype.h>

#if (defined __APPLE__) || (defined __FreeBSD__)
    #include <xlocale.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    int       p101_iswalnum_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswalpha_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswblank_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswcntrl_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswctype_l(const struct p101_env *env, wint_t wc, wctype_t charclass, locale_t locale);
    int       p101_iswdigit_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswgraph_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswlower_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswprint_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswpunct_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswspace_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswupper_l(const struct p101_env *env, wint_t wc, locale_t locale);
    int       p101_iswxdigit_l(const struct p101_env *env, wint_t wc, locale_t locale);
    wint_t    p101_towctrans_l(const struct p101_env *env, wint_t wc, wctrans_t desc, locale_t locale);
    wint_t    p101_towlower_l(const struct p101_env *env, wint_t wc, locale_t locale);
    wint_t    p101_towupper_l(const struct p101_env *env, wint_t wc, locale_t locale);
    wctrans_t p101_wctrans_l(const struct p101_env *env, struct p101_error *err, const char *charclass, locale_t locale);
    wctype_t  p101_wctype_l(const struct p101_env *env, const char *property, locale_t locale);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_WCTYPE_H
