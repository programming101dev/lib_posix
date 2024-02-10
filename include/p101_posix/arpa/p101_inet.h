#ifndef LIBP101_POSIX_ARPA_P101_INET_H
#define LIBP101_POSIX_ARPA_P101_INET_H

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

#include <arpa/inet.h>
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    uint32_t    p101_htonl(const struct p101_env *env, uint32_t hostlong);
    uint16_t    p101_htons(const struct p101_env *env, uint16_t hostshort);
    uint32_t    p101_ntohl(const struct p101_env *env, uint32_t netlong);
    uint16_t    p101_ntohs(const struct p101_env *env, uint16_t netshort);
    in_addr_t   p101_inet_addr(const struct p101_env *env, struct p101_error *err, const char *cp);
    char       *p101_inet_ntoa(const struct p101_env *env, struct in_addr in);
    const char *p101_inet_ntop(const struct p101_env *env, struct p101_error *err, int af, const void *restrict src, char *restrict dst, socklen_t size);
    int         p101_inet_pton(const struct p101_env *env, struct p101_error *err, int af, const char *restrict src, void *restrict dst);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_ARPA_P101_INET_H
