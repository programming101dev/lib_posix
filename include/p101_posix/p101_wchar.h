#ifndef LIBP101_POSIX_P101_WCHAR_H
#define LIBP101_POSIX_P101_WCHAR_H

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
#include <wchar.h>

#if(defined __APPLE__) || (defined __FreeBSD__)
    #include <xlocale.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    size_t   p101_mbsnrtowcs(const struct p101_env *env, struct p101_error *err, wchar_t *restrict dst, const char **restrict src, size_t nmc, size_t len, mbstate_t *restrict ps);
    FILE    *p101_open_wmemstream(const struct p101_env *env, struct p101_error *err, wchar_t **bufp, size_t *sizep);
    wchar_t *p101_wcpcpy(const struct p101_env *env, wchar_t *restrict ws1, const wchar_t *restrict ws2);
    wchar_t *p101_wcpncpy(const struct p101_env *env, wchar_t *restrict ws1, const wchar_t *restrict ws2, size_t n);
    int      p101_wcscasecmp(const struct p101_env *env, const wchar_t *ws1, const wchar_t *ws2);
    int      p101_wcscasecmp_l(const struct p101_env *env, const wchar_t *ws1, const wchar_t *ws2, locale_t locale);
    int      p101_wcscoll_l(const struct p101_env *env, struct p101_error *err, const wchar_t *ws1, const wchar_t *ws2, locale_t locale);
    wchar_t *p101_wcsdup(const struct p101_env *env, struct p101_error *err, const wchar_t *string);
    int      p101_wcsncasecmp(const struct p101_env *env, const wchar_t *ws1, const wchar_t *ws2, size_t n);
    size_t   p101_wcsnlen(const struct p101_env *env, const wchar_t *ws, size_t maxlen);
    size_t   p101_wcsnrtombs(const struct p101_env *env, struct p101_error *err, char *restrict dst, const wchar_t **restrict src, size_t nwc, size_t len, mbstate_t *restrict ps);
    size_t   p101_wcsxfrm_l(const struct p101_env *env, struct p101_error *err, wchar_t *restrict ws1, const wchar_t *restrict ws2, size_t n, locale_t locale);

#ifdef __cplusplus
}
#endif

// not on FreeBSD
// int p101_wcsncasecmp_l(const struct p101_env *env, const wchar_t *ws1, const wchar_t *ws2, size_t n, locale_t locale);

#endif    // LIBP101_POSIX_P101_WCHAR_H
