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

#include "p101_posix/sys/p101_socket.h"

int p101_accept(const struct p101_env *env, struct p101_error *err, int socket, struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = accept(socket, address, address_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_bind(const struct p101_env *env, struct p101_error *err, int socket, const struct sockaddr *address, socklen_t address_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = bind(socket, address, address_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_connect(const struct p101_env *env, struct p101_error *err, int socket, const struct sockaddr *address, socklen_t address_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = connect(socket, address, address_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_getpeername(const struct p101_env *env, struct p101_error *err, int socket, struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpeername(socket, address, address_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_getsockname(const struct p101_env *env, struct p101_error *err, int socket, struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getsockname(socket, address, address_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_getsockopt(const struct p101_env *env, struct p101_error *err, int socket, int level, int option_name, void *restrict option_value, socklen_t *restrict option_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getsockopt(socket, level, option_name, option_value, option_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_listen(const struct p101_env *env, struct p101_error *err, int socket, int backlog)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = listen(socket, backlog);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_recv(const struct p101_env *env, struct p101_error *err, int socket, void *buffer, size_t length, int flags)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = recv(socket, buffer, length, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_recvfrom(const struct p101_env *env, struct p101_error *err, int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = recvfrom(socket, buffer, length, flags, address, address_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_recvmsg(const struct p101_env *env, struct p101_error *err, int socket, struct msghdr *message, int flags)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = recvmsg(socket, message, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_send(const struct p101_env *env, struct p101_error *err, int socket, const void *buffer, size_t length, int flags)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = send(socket, buffer, length, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_sendmsg(const struct p101_env *env, struct p101_error *err, int socket, const struct msghdr *message, int flags)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sendmsg(socket, message, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_sendto(const struct p101_env *env, struct p101_error *err, int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sendto(socket, message, length, flags, dest_addr, dest_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setsockopt(const struct p101_env *env, struct p101_error *err, int socket, int level, int option_name, const void *option_value, socklen_t option_len)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setsockopt(socket, level, option_name, option_value, option_len);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_shutdown(const struct p101_env *env, struct p101_error *err, int socket, int how)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = shutdown(socket, how);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_sockatmark(const struct p101_env *env, struct p101_error *err, int s)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sockatmark(s);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_socket(const struct p101_env *env, struct p101_error *err, int domain, int type, int protocol)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = socket(domain, type, protocol);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_socketpair(const struct p101_env *env, struct p101_error *err, int domain, int type, int protocol, int socket_vector[2])
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = socketpair(domain, type, protocol, socket_vector);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
