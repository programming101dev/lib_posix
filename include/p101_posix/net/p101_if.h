#ifndef LIBP101_POSIX_NET_P101_IF_H
#define LIBP101_POSIX_NET_P101_IF_H

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

#include <net/if.h>
#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void                 p101_if_freenameindex(const struct p101_env *env, struct if_nameindex *ptr);
    char                *p101_if_indextoname(const struct p101_env *env, struct p101_error *err, unsigned ifindex, char *ifname);
    struct if_nameindex *p101_if_nameindex(const struct p101_env *env, struct p101_error *err);
    unsigned             p101_if_nametoindex(const struct p101_env *env, const char *ifname);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_NET_P101_IF_H
