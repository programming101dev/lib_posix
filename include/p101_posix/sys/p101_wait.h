#ifndef LIBP101_POSIX_SYS_P101_WAIT_H
#define LIBP101_POSIX_SYS_P101_WAIT_H

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
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef __cplusplus
extern "C"
{
#endif

    pid_t p101_wait(const struct p101_env *env, struct p101_error *err, int *stat_loc);
    int   p101_waitid(const struct p101_env *env, struct p101_error *err, idtype_t idtype, id_t id, siginfo_t *infop, int options);
    pid_t p101_waitpid(const struct p101_env *env, struct p101_error *err, pid_t pid, int *stat_loc, int options);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_SYS_P101_WAIT_H
