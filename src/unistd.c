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

#include "p101_posix/p101_unistd.h"

// #include <unistd.h>

int p101_access(const struct p101_env *env, struct p101_error *err, const char *path, int amode)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = access(path, amode);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

unsigned p101_alarm(const struct p101_env *env, unsigned seconds)
{
    unsigned ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = alarm(seconds);

    return ret_val;
}

int p101_chdir(const struct p101_env *env, struct p101_error *err, const char *path)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = chdir(path);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_chown(const struct p101_env *env, struct p101_error *err, const char *path, uid_t owner, gid_t group)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = chown(path, owner, group);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_close(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = close(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

size_t p101_confstr(const struct p101_env *env, struct p101_error *err, int name, char *buf, size_t len)
{
    size_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = confstr(name, buf, len);

    if(ret_val == 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_dup(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dup(fildes);    // NOLINT(android-cloexec-dup)

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_dup2(const struct p101_env *env, struct p101_error *err, int fildes, int fildes2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dup2(fildes, fildes2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

void p101__exit(const struct p101_env *env, int status)
{
    P101_TRACE(env);
    errno = 0;
    _exit(status);
}

int p101_execv(const struct p101_env *env, struct p101_error *err, const char *path, char *const argv[])
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = execv(path, argv);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_execve(const struct p101_env *env, struct p101_error *err, const char *path, char *const argv[], char *const envp[])
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = execve(path, argv, envp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_execvp(const struct p101_env *env, struct p101_error *err, const char *file, char *const argv[])
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = execvp(file, argv);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_faccessat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int amode, int flag)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = faccessat(fd, path, amode, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_fchdir(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fchdir(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_fchown(const struct p101_env *env, struct p101_error *err, int fildes, uid_t owner, gid_t group)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fchown(fildes, owner, group);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_fchownat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, uid_t owner, gid_t group, int flag)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fchownat(fd, path, owner, group, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

pid_t p101_fork(const struct p101_env *env, struct p101_error *err)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fork();

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

long p101_fpathconf(const struct p101_env *env, struct p101_error *err, int fildes, int name)
{
    long ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = fpathconf(fildes, name);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_ftruncate(const struct p101_env *env, struct p101_error *err, int fildes, off_t length)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ftruncate(fildes, length);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

char *p101_getcwd(const struct p101_env *env, struct p101_error *err, char *buf, size_t size)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getcwd(buf, size);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

gid_t p101_getegid(const struct p101_env *env)
{
    gid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getegid();

    return ret_val;
}

uid_t p101_geteuid(const struct p101_env *env)
{
    uid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = geteuid();

    return ret_val;
}

gid_t p101_getgid(const struct p101_env *env)
{
    gid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getgid();

    return ret_val;
}

int p101_getgroups(const struct p101_env *env, struct p101_error *err, int gidsetsize, gid_t grouplist[])
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getgroups(gidsetsize, grouplist);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_gethostname(const struct p101_env *env, struct p101_error *err, char *name, size_t namelen)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = gethostname(name, namelen);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

/*
char *p101_getlogin(const struct p101_env *env, struct p101_error *err)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getlogin();

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
*/

int p101_getlogin_r(const struct p101_env *env, struct p101_error *err, char *name, size_t namesize)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getlogin_r(name, namesize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    return ret_val;
}

int p101_getopt(const struct p101_env *env, int argc, char *const argv[], const char *optstring)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getopt(argc, argv, optstring);

    return ret_val;
}

pid_t p101_getpgid(const struct p101_env *env, struct p101_error *err, pid_t pid)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpgid(pid);

    if(ret_val == (pid_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

pid_t p101_getpgrp(const struct p101_env *env)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpgrp();

    return ret_val;
}

pid_t p101_getpid(const struct p101_env *env)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpid();

    return ret_val;
}

pid_t p101_getppid(const struct p101_env *env)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getppid();

    return ret_val;
}

pid_t p101_getsid(const struct p101_env *env, struct p101_error *err, pid_t pid)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getsid(pid);

    if(ret_val == (pid_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

uid_t p101_getuid(const struct p101_env *env)
{
    uid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getuid();

    return ret_val;
}

int p101_isatty(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = isatty(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_lchown(const struct p101_env *env, struct p101_error *err, const char *path, uid_t owner, gid_t group)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = lchown(path, owner, group);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_link(const struct p101_env *env, struct p101_error *err, const char *path1, const char *path2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = link(path1, path2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_linkat(const struct p101_env *env, struct p101_error *err, int fd1, const char *path1, int fd2, const char *path2, int flag)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = linkat(fd1, path1, fd2, path2, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

off_t p101_lseek(const struct p101_env *env, struct p101_error *err, int fildes, off_t offset, int whence)
{
    off_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = lseek(fildes, offset, whence);

    if(ret_val == (off_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

long p101_pathconf(const struct p101_env *env, struct p101_error *err, const char *path, int name)
{
    long ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pathconf(path, name);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_pause(const struct p101_env *env, struct p101_error *err)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pause();

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_pipe(const struct p101_env *env, struct p101_error *err, int fildes[2])
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pipe(fildes);    // NOLINT(android-cloexec-pipe)

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_pread(const struct p101_env *env, struct p101_error *err, int fildes, void *buf, size_t nbyte, off_t offset)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pread(fildes, buf, nbyte, offset);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_pwrite(const struct p101_env *env, struct p101_error *err, int fildes, const void *buf, size_t nbyte, off_t offset)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pwrite(fildes, buf, nbyte, offset);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_read(const struct p101_env *env, struct p101_error *err, int fildes, void *buf, size_t nbyte)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = read(fildes, buf, nbyte);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_readlink(const struct p101_env *env, struct p101_error *err, const char *restrict path, char *restrict buf, size_t bufsize)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = readlink(path, buf, bufsize);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_readlinkat(const struct p101_env *env, struct p101_error *err, int fd, const char *restrict path, char *restrict buf, size_t bufsize)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = readlinkat(fd, path, buf, bufsize);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_rmdir(const struct p101_env *env, struct p101_error *err, const char *path)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = rmdir(path);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setegid(const struct p101_env *env, struct p101_error *err, gid_t gid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setegid(gid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_seteuid(const struct p101_env *env, struct p101_error *err, uid_t uid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = seteuid(uid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setgid(const struct p101_env *env, struct p101_error *err, gid_t gid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setgid(gid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setpgid(const struct p101_env *env, struct p101_error *err, pid_t pid, pid_t pgid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setpgid(pid, pgid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

pid_t p101_setsid(const struct p101_env *env, struct p101_error *err)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setsid();

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setuid(const struct p101_env *env, struct p101_error *err, uid_t uid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setuid(uid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

unsigned p101_sleep(const struct p101_env *env, unsigned seconds)
{
    unsigned ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sleep(seconds);

    return ret_val;
}

int p101_symlink(const struct p101_env *env, struct p101_error *err, const char *path1, const char *path2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = symlink(path1, path2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_symlinkat(const struct p101_env *env, struct p101_error *err, const char *path1, int fd, const char *path2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = symlinkat(path1, fd, path2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

long p101_sysconf(const struct p101_env *env, struct p101_error *err, int name)
{
    long ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sysconf(name);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

pid_t p101_tcgetpgrp(const struct p101_env *env, struct p101_error *err, int fildes)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcgetpgrp(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_tcsetpgrp(const struct p101_env *env, struct p101_error *err, int fildes, pid_t pgid_id)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tcsetpgrp(fildes, pgid_id);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_truncate(const struct p101_env *env, struct p101_error *err, const char *path, off_t length)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = truncate(path, length);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

/*
char *p101_ttyname(const struct p101_env *env, struct p101_error *err, int fildes)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ttyname(fildes);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
*/

int p101_ttyname_r(const struct p101_env *env, struct p101_error *err, int fildes, char *name, size_t namesize)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ttyname_r(fildes, name, namesize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    return ret_val;
}

int p101_unlink(const struct p101_env *env, struct p101_error *err, const char *path)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = unlink(path);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_unlinkat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int flag)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = unlinkat(fd, path, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_write(const struct p101_env *env, struct p101_error *err, int fildes, const void *buf, size_t nbyte)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = write(fildes, buf, nbyte);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
