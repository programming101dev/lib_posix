#ifndef LIBP101_POSIX_P101_STRING_H
#define LIBP101_POSIX_P101_STRING_H

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

#include <p101_env/env.h>

#if (defined __APPLE__) || (defined __FreeBSD__)
    #include <xlocale.h>
#else
    #include <locale.h>
#endif

char  *p101_stpcpy(const struct p101_env *env, char *restrict s1, const char *restrict s2);
char  *p101_stpncpy(const struct p101_env *env, char *restrict s1, const char *restrict s2, size_t n);
int    p101_strcoll_l(const struct p101_env *env, struct p101_error *err, const char *s1, const char *s2, locale_t locale);
char  *p101_strdup(const struct p101_env *env, struct p101_error *err, const char *s);
int    p101_strerror_r(const struct p101_env *env, struct p101_error *err, int errnum, char *strerrbuf, size_t buflen);
char  *p101_strndup(const struct p101_env *env, struct p101_error *err, const char *s, size_t size);
size_t p101_strnlen(const struct p101_env *env, const char *s, size_t maxlen);
char  *p101_strsignal(const struct p101_env *env, int signum);
char  *p101_strtok_r(const struct p101_env *env, char *restrict s, const char *restrict sep, char **restrict state);
size_t p101_strxfrm_l(const struct p101_env *env, struct p101_error *err, char *restrict s1, const char *restrict s2, size_t n, locale_t locale);

#ifdef __cplusplus
extern "C"
{
#endif

    // not on macOS
    // char *p101_strerror_l(const struct p101_env *env, struct p101_error *err, int errnum, locale_t locale);

#endif    // LIBP101_POSIX_P101_STRING_H
