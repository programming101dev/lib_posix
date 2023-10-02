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

#include "p101_posix/p101_netdb.h"

void p101_endhostent(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    endhostent();
}

void p101_endnetent(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    endnetent();
}

void p101_endprotoent(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    endprotoent();
}

void p101_endservent(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    endservent();
}

void p101_freeaddrinfo(const struct p101_env *env, struct addrinfo *ai)
{
    P101_TRACE(env);
    errno = 0;
    freeaddrinfo(ai);
}

const char *p101_gai_strerror(const struct p101_env *env, int ecode)
{
    const char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = gai_strerror(ecode);

    return ret_val;
}

int p101_getaddrinfo(const struct p101_env *env, struct p101_error *err, const char *restrict nodename, const char *restrict servname, const struct addrinfo *restrict hints,
                     struct addrinfo **restrict res)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getaddrinfo(nodename, servname, hints, res);

    if(ret_val != 0)
    {
        // TODO: message
        P101_ERROR_RAISE_SYSTEM(err, "", ret_val);
    }

    return ret_val;
}

struct hostent *p101_gethostent(const struct p101_env *env)
{
    struct hostent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = gethostent();

    return ret_val;
}

int p101_getnameinfo(const struct p101_env *env, struct p101_error *err, const struct sockaddr *restrict sa, socklen_t salen, char *restrict node, socklen_t nodelen,
                     char *restrict service, socklen_t servicelen, int flags)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getnameinfo(sa, salen, node, nodelen, service, servicelen, flags);

    if(ret_val != 0)
    {
        // TODO: message
        P101_ERROR_RAISE_SYSTEM(err, "", ret_val);
    }

    return ret_val;
}

struct netent *p101_getnetbyaddr(const struct p101_env *env, uint32_t net, int type)
{
    struct netent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getnetbyaddr(net, type);

    return ret_val;
}

struct netent *p101_getnetbyname(const struct p101_env *env, const char *name)
{
    struct netent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getnetbyname(name);

    return ret_val;
}

struct netent *p101_getnetent(const struct p101_env *env)
{
    struct netent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getnetent();

    return ret_val;
}

struct protoent *p101_getprotobyname(const struct p101_env *env, const char *name)
{
    struct protoent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getprotobyname(name);

    return ret_val;
}

struct protoent *p101_getprotobynumber(const struct p101_env *env, int proto)
{
    struct protoent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getprotobynumber(proto);

    return ret_val;
}

struct protoent *p101_getprotoent(const struct p101_env *env)
{
    struct protoent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getprotoent();

    return ret_val;
}

struct servent *p101_getservbyname(const struct p101_env *env, const char *name, const char *proto)
{
    struct servent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getservbyname(name, proto);

    return ret_val;
}

struct servent *p101_getservbyport(const struct p101_env *env, int port, const char *proto)
{
    struct servent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getservbyport(port, proto);

    return ret_val;
}

struct servent *p101_getservent(const struct p101_env *env)
{
    struct servent *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getservent();

    return ret_val;
}

void p101_sethostent(const struct p101_env *env, int stayopen)
{
    P101_TRACE(env);
    errno = 0;
    sethostent(stayopen);
}

void p101_setnetent(const struct p101_env *env, int stayopen)
{
    P101_TRACE(env);
    errno = 0;
    setnetent(stayopen);
}

void p101_setprotoent(const struct p101_env *env, int stayopen)
{
    P101_TRACE(env);
    errno = 0;
    setprotoent(stayopen);
}

void p101_setservent(const struct p101_env *env, int stayopen)
{
    P101_TRACE(env);
    errno = 0;
    setservent(stayopen);
}
