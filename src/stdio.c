/*
 *Copyright 2021-2024 D'Arcy Smith.
 *
 *Licensed under the Apache License, Version 2.0 (the "License");
 *you may not use this file except in compliance with the License.
 *You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *Unless required by applicable law or agreed to in writing, software
 *distributed under the License is distributed on an "AS IS" BASIS,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *See the License for the specific language governing permissions and
 *limitations under the License.
 */

#include "p101_posix/p101_stdio.h"

char *p101_ctermid(const struct p101_env *env, char *s)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ctermid(s);

    return ret_val;
}

FILE *p101_fdopen(const struct p101_env *env, struct p101_error *err, int fildes, const char *mode)
{
    FILE *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fdopen(fildes, mode);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_fileno(const struct p101_env *env, struct p101_error *err, FILE *stream)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fileno(stream);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

void p101_flockfile(const struct p101_env *env, FILE *file)
{
    P101_TRACE(env);
    errno = 0;
    flockfile(file);
}

FILE *p101_fmemopen(const struct p101_env *env, struct p101_error *err, void *restrict buf, size_t size, const char *restrict mode)
{
    FILE *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fmemopen(buf, size, mode);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_fseeko(const struct p101_env *env, struct p101_error *err, FILE *stream, off_t offset, int whence)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fseeko(stream, offset, whence);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

off_t p101_ftello(const struct p101_env *env, struct p101_error *err, FILE *stream)
{
    off_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ftello(stream);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_ftrylockfile(const struct p101_env *env, FILE *file)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ftrylockfile(file);

    if(ret_val != 0)
    {
        // TODO: what?
    }

    return ret_val;
}

void p101_funlockfile(const struct p101_env *env, FILE *file)
{
    P101_TRACE(env);
    errno = 0;
    funlockfile(file);
}

int p101_getc_unlocked(const struct p101_env *env, struct p101_error *err, FILE *stream)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
#ifdef __GNUC__
    #pragma GCC diagnostic push
//    #pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
    #pragma GCC diagnostic ignored "-Wstrict-overflow"
#endif
    ret_val = getc_unlocked(stream);
#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif

    if(ret_val == EOF && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_getchar_unlocked(const struct p101_env *env, struct p101_error *err)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
#ifdef __GNUC__
    #pragma GCC diagnostic push
//    #pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
    #pragma GCC diagnostic ignored "-Wstrict-overflow"
#endif
    ret_val = getchar_unlocked();
#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif

    if(ret_val == EOF && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_getdelim(const struct p101_env *env, struct p101_error *err, char **restrict lineptr, size_t *restrict n, int delimiter, FILE *restrict stream)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getdelim(lineptr, n, delimiter, stream);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_getline(const struct p101_env *env, struct p101_error *err, char **restrict lineptr, size_t *restrict n, FILE *restrict stream)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getline(lineptr, n, stream);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

FILE *p101_open_memstream(const struct p101_env *env, struct p101_error *err, char **bufp, size_t *sizep)
{
    FILE *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = open_memstream(bufp, sizep);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_pclose(const struct p101_env *env, struct p101_error *err, FILE *stream)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pclose(stream);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

FILE *p101_popen(const struct p101_env *env, struct p101_error *err, const char *command, const char *mode)
{
    FILE *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = popen(command, mode);    // NOLINT(cert-env33-c)

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_putc_unlocked(const struct p101_env *env, struct p101_error *err, int c, FILE *stream)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = putc_unlocked(c, stream);

    if(ret_val == EOF)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_putchar_unlocked(const struct p101_env *env, struct p101_error *err, int c)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = putchar_unlocked(c);

    if(ret_val == EOF)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_renameat(const struct p101_env *env, struct p101_error *err, int oldfd, const char *old_name, int newfd, const char *new_name)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = renameat(oldfd, old_name, newfd, new_name);

    if(ret_val == EOF)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_vdprintf(const struct p101_env *env, struct p101_error *err, int fildes, const char *restrict format, va_list ap)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    ret_val = vdprintf(fildes, format, ap);
#pragma GCC diagnostic pop

    if(ret_val < 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
