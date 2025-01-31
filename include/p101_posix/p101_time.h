#ifndef LIBP101_POSIX_P101_TIME_H
#define LIBP101_POSIX_P101_TIME_H

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
#include <time.h>

#if (defined __APPLE__) || (defined __FreeBSD__)
    #include <xlocale.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    int        p101_clock_getres(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, struct timespec *res);
    int        p101_clock_gettime(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, struct timespec *tp);
    int        p101_clock_settime(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, const struct timespec *tp);
    struct tm *p101_gmtime_r(const struct p101_env *env, struct p101_error *err, const time_t *restrict timer, struct tm *restrict result);
    struct tm *p101_localtime_r(const struct p101_env *env, struct p101_error *err, const time_t *restrict timer, struct tm *restrict result);
    int        p101_nanosleep(const struct p101_env *env, struct p101_error *err, const struct timespec *rqtp, struct timespec *rmtp);
    size_t     p101_strftime_l(const struct p101_env *env, char *restrict s, size_t maxsize, const char *restrict format, const struct tm *restrict timeptr, locale_t locale);
    void       p101_tzset(const struct p101_env *env);

#ifdef __cplusplus
}
#endif

// not on macOS
// int p101_timer_create(const struct p101_env *env, struct p101_error *err, clockid_t clockid, struct sigevent *restrict evp, timer_t *restrict timerid);
// int p101_timer_delete(const struct p101_env *env, struct p101_error *err, timer_t timerid);
// int p101_timer_getoverrun(const struct p101_env *env, struct p101_error *err, timer_t timerid);
// int p101_timer_gettime(const struct p101_env *env, struct p101_error *err, timer_t timerid, struct itimerspec *value);
// int p101_timer_settime(const struct p101_env *env, struct p101_error *err, timer_t timerid, int flags, const struct itimerspec *restrict value, struct itimerspec *restrict
// ovalue); int p101_clock_nanosleep(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, int flags, const struct timespec *rqtp, struct timespec *rmtp);

#endif    // LIBP101_POSIX_P101_TIME_H
