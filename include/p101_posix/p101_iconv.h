#ifndef LIBP101_POSIX_P101_ICONV_H
#define LIBP101_POSIX_P101_ICONV_H

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

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-identifier"
#endif
#include <iconv.h>
#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    size_t  p101_iconv(const struct p101_env *env, struct p101_error *err, iconv_t cd, char **restrict inbuf, size_t *restrict inbytesleft, char **restrict outbuf,
                       size_t *restrict outbytesleft);
    int     p101_iconv_close(const struct p101_env *env, struct p101_error *err, iconv_t cd);
    iconv_t p101_iconv_open(const struct p101_env *env, struct p101_error *err, const char *tocode, const char *fromcode);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_ICONV_H
