#ifndef LIBP101_POSIX_P101_NETDB_H
#define LIBP101_POSIX_P101_NETDB_H

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

#include <netdb.h>
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void             p101_endhostent(const struct p101_env *env);
    void             p101_endnetent(const struct p101_env *env);
    void             p101_endprotoent(const struct p101_env *env);
    void             p101_endservent(const struct p101_env *env);
    void             p101_freeaddrinfo(const struct p101_env *env, struct addrinfo *ai);
    const char      *p101_gai_strerror(const struct p101_env *env, int ecode);
    int              p101_getaddrinfo(const struct p101_env *env, struct p101_error *err, const char *restrict nodename, const char *restrict servname, const struct addrinfo *restrict hints, struct addrinfo **restrict res);
    struct hostent  *p101_gethostent(const struct p101_env *env);
    int              p101_getnameinfo(const struct p101_env *env, struct p101_error *err, const struct sockaddr *restrict sa, socklen_t salen, char *restrict node, socklen_t nodelen, char *restrict service, socklen_t servicelen, int flags);
    struct netent   *p101_getnetbyaddr(const struct p101_env *env, uint32_t net, int type);
    struct netent   *p101_getnetbyname(const struct p101_env *env, const char *name);
    struct netent   *p101_getnetent(const struct p101_env *env);
    struct protoent *p101_getprotobyname(const struct p101_env *env, const char *name);
    struct protoent *p101_getprotobynumber(const struct p101_env *env, int proto);
    struct protoent *p101_getprotoent(const struct p101_env *env);
    struct servent  *p101_getservbyname(const struct p101_env *env, const char *name, const char *proto);
    struct servent  *p101_getservbyport(const struct p101_env *env, int port, const char *proto);
    struct servent  *p101_getservent(const struct p101_env *env);
    void             p101_sethostent(const struct p101_env *env, int stayopen);
    void             p101_setnetent(const struct p101_env *env, int stayopen);
    void             p101_setprotoent(const struct p101_env *env, int stayopen);
    void             p101_setservent(const struct p101_env *env, int stayopen);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_P101_NETDB_H
