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

#include "p101_posix/p101_termios.h"

speed_t p101_cfgetispeed(const struct p101_env *env, const struct termios *termios_p)
{
    speed_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = cfgetispeed(termios_p);

    return ret_val;
}

speed_t p101_cfgetospeed(const struct p101_env *env, const struct termios *termios_p)
{
    speed_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = cfgetospeed(termios_p);

    return ret_val;
}

int p101_cfsetispeed(const struct p101_env *env, struct p101_error *err, struct termios *termios_p, speed_t speed)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = cfsetispeed(termios_p, speed);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_cfsetospeed(const struct p101_env *env, struct p101_error *err, struct termios *termios_p, speed_t speed)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = cfsetospeed(termios_p, speed);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcdrain(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcdrain(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcflow(const struct p101_env *env, struct p101_error *err, int fildes, int action)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcflow(fildes, action);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcflush(const struct p101_env *env, struct p101_error *err, int fildes, int queue_selector)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcflush(fildes, queue_selector);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcgetattr(const struct p101_env *env, struct p101_error *err, int fildes, struct termios *termios_p)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcgetattr(fildes, termios_p);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

pid_t p101_tcgetsid(const struct p101_env *env, struct p101_error *err, int fildes)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcgetsid(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcsendbreak(const struct p101_env *env, struct p101_error *err, int fildes, int duration)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcsendbreak(fildes, duration);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcsetattr(const struct p101_env *env, struct p101_error *err, int fildes, int optional_actions, const struct termios *termios_p)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcsetattr(fildes, optional_actions, termios_p);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
