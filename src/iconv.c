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

#include "p101_posix/p101_iconv.h"

size_t p101_iconv(const struct p101_env *env, struct p101_error *err, iconv_t cd, char **restrict inbuf, size_t *restrict inbytesleft, char **restrict outbuf,
                  size_t *restrict outbytesleft)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iconv(cd, inbuf, inbytesleft, outbuf, outbytesleft);

    if(ret_val == (size_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_iconv_close(const struct p101_env *env, struct p101_error *err, iconv_t cd)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iconv_close(cd);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

iconv_t p101_iconv_open(const struct p101_env *env, struct p101_error *err, const char *tocode, const char *fromcode)
{
    iconv_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = iconv_open(tocode, fromcode);

    if(ret_val == (iconv_t)-1)    // NOLINT(performance-no-int-to-ptr)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
