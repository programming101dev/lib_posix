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

#include "p101_posix/p101_wctype.h"

int p101_iswalnum_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswalnum_l(wc, locale);

    return ret_val;
}

int p101_iswalpha_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswalpha_l(wc, locale);

    return ret_val;
}

int p101_iswblank_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswblank_l(wc, locale);

    return ret_val;
}

int p101_iswcntrl_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswcntrl_l(wc, locale);

    return ret_val;
}

int p101_iswctype_l(const struct p101_env *env, wint_t wc, wctype_t charclass, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswctype_l(wc, charclass, locale);

    return ret_val;
}

int p101_iswdigit_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswdigit_l(wc, locale);

    return ret_val;
}

int p101_iswgraph_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswgraph_l(wc, locale);

    return ret_val;
}

int p101_iswlower_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswlower_l(wc, locale);

    return ret_val;
}

int p101_iswprint_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswprint_l(wc, locale);

    return ret_val;
}

int p101_iswpunct_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswpunct_l(wc, locale);

    return ret_val;
}

int p101_iswspace_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswspace_l(wc, locale);

    return ret_val;
}

int p101_iswupper_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswupper_l(wc, locale);

    return ret_val;
}

int p101_iswxdigit_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iswxdigit_l(wc, locale);

    return ret_val;
}

wint_t p101_towctrans_l(const struct p101_env *env, wint_t wc, wctrans_t desc, locale_t locale)
{
    wint_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = towctrans_l(wc, desc, locale);

    return ret_val;
}

wint_t p101_towlower_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    wint_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = towlower_l(wc, locale);

    return ret_val;
}

wint_t p101_towupper_l(const struct p101_env *env, wint_t wc, locale_t locale)
{
    wint_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = towupper_l(wc, locale);

    return ret_val;
}

wctrans_t p101_wctrans_l(const struct p101_env *env, struct p101_error *err, const char *charclass, locale_t locale)
{
    wctrans_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wctrans_l(charclass, locale);

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

wctype_t p101_wctype_l(const struct p101_env *env, const char *property, locale_t locale)
{
    wctype_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wctype_l(property, locale);

    return ret_val;
}
