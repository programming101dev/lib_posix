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

#include "p101_posix/p101_wchar.h"

size_t p101_mbsnrtowcs(const struct p101_env *env, struct p101_error *err, wchar_t *restrict dst, const char **restrict src, size_t nmc, size_t len, mbstate_t *restrict ps)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = mbsnrtowcs(dst, src, nmc, len, ps);

    if(ret_val == (size_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

FILE *p101_open_wmemstream(const struct p101_env *env, struct p101_error *err, wchar_t **bufp, size_t *sizep)
{
    FILE *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = open_wmemstream(bufp, sizep);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

wchar_t *p101_wcpcpy(const struct p101_env *env, wchar_t *restrict ws1, const wchar_t *restrict ws2)
{
    wchar_t *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcpcpy(ws1, ws2);

    return ret_val;
}

wchar_t *p101_wcpncpy(const struct p101_env *env, wchar_t *restrict ws1, const wchar_t *restrict ws2, size_t n)
{
    wchar_t *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcpncpy(ws1, ws2, n);

    return ret_val;
}

int p101_wcscasecmp(const struct p101_env *env, const wchar_t *ws1, const wchar_t *ws2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcscasecmp(ws1, ws2);

    return ret_val;
}

int p101_wcscoll_l(const struct p101_env *env, struct p101_error *err, const wchar_t *ws1, const wchar_t *ws2, locale_t locale)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcscoll_l(ws1, ws2, locale);

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

wchar_t *p101_wcsdup(const struct p101_env *env, struct p101_error *err, const wchar_t *string)
{
    wchar_t *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcsdup(string);

    if(ret_val != NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_wcsncasecmp(const struct p101_env *env, const wchar_t *ws1, const wchar_t *ws2, size_t n)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcsncasecmp(ws1, ws2, n);

    return ret_val;
}

size_t p101_wcsnlen(const struct p101_env *env, const wchar_t *ws, size_t maxlen)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcsnlen(ws, maxlen);

    return ret_val;
}

size_t p101_wcsnrtombs(const struct p101_env *env, struct p101_error *err, char *restrict dst, const wchar_t **restrict src, size_t nwc, size_t len, mbstate_t *restrict ps)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcsnrtombs(dst, src, nwc, len, ps);

    if(ret_val != (size_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

size_t p101_wcsxfrm_l(const struct p101_env *env, struct p101_error *err, wchar_t *restrict ws1, const wchar_t *restrict ws2, size_t n, locale_t locale)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcsxfrm_l(ws1, ws2, n, locale);

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
