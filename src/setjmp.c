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

#include "p101_posix/p101_setjmp.h"

void p101_siglongjmp(const struct p101_env *env, sigjmp_buf jmpbuf, int val)
{
    P101_TRACE(env);
    errno = 0;
    siglongjmp(jmpbuf, val);
}

int p101_sigsetjmp(const struct p101_env *env, sigjmp_buf jmpbuf, int savemask)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sigsetjmp(jmpbuf, savemask);

    return ret_val;
}
