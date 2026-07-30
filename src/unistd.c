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

#include "p101_posix/p101_unistd.h"
#include "p101_posix_internal.h"

int p101_access(const struct p101_env *env, struct p101_error *err, const char *path, int amode)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = access(path, amode);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

unsigned p101_alarm(const struct p101_env *env, unsigned seconds)
{
    unsigned ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = alarm(seconds);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_chdir(const struct p101_env *env, struct p101_error *err, const char *path)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = chdir(path);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_chown(const struct p101_env *env, struct p101_error *err, const char *path, uid_t owner, gid_t group)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = chown(path, owner, group);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_close(const struct p101_env *env, struct p101_error *err, int fildes)
{
    errno_t actual_error;
    int     ret_val;
    int     fault;

    P101_TRACE(env);
    fault = p101_env_check_fault(env, "close");

    if(fault != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, fault);
        P101_TRACE_EXIT(env);

        return -1;
    }

    errno        = 0;
    ret_val      = close(fildes);
    actual_error = errno;

    if(ret_val == -1)
    {
        if(actual_error == EBADF)
        {
            P101_TRACK_CLOSE(env, fildes);
        }
        P101_ERROR_RAISE_ERRNO(err, actual_error);
    }
    else
    {
        P101_TRACK_CLOSE(env, fildes);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}

size_t p101_confstr(const struct p101_env *env, struct p101_error *err, int name, char *buf, size_t len)
{
    size_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, 0);
    errno   = 0;
    ret_val = confstr(name, buf, len);

    if(ret_val == 0 && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_dup(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;
    int fault;

    P101_TRACE(env);
    fault = p101_env_check_fault(env, "dup");

    if(fault != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, fault);
        P101_TRACE_EXIT(env);

        return -1;
    }

    errno   = 0;
    ret_val = dup(fildes);    // NOLINT(android-cloexec-dup)

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        P101_TRACK_OPEN(env, ret_val);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}

int p101_dup2(const struct p101_env *env, struct p101_error *err, int fildes, int fildes2)
{
    int ret_val;
    int fault;

    P101_TRACE(env);
    fault = p101_env_check_fault(env, "dup2");

    if(fault != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, fault);
        P101_TRACE_EXIT(env);

        return -1;
    }

    errno   = 0;
    ret_val = dup2(fildes, fildes2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        /* dup2() SILENTLY closes fildes2 if it was already open, so the
         * ledger retires the old entry before recording the new one.
         * Retiring an untracked descriptor is a no-op, and when
         * fildes == fildes2 dup2() does nothing -- the net effect here is
         * still one tracked descriptor, now attributed to this call site. */
        P101_TRACK_CLOSE(env, fildes2);
        P101_TRACK_OPEN(env, ret_val);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}

void p101_posix_exit_immediately(const struct p101_env *env, int status)
{
    P101_TRACE(env);
    errno = 0;
    P101_TRACE_EXIT(env);
    p101_env_complete_event_streams(env);
    _exit(status);
}

int p101_execv(const struct p101_env *env, struct p101_error *err, const char *path, char *const argv[])
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    P101_TRACK_EXEC(env, path);
    errno   = 0;
    ret_val = execv(path, argv);

    if(ret_val == -1)
    {
        int actual_error;

        actual_error = errno;
        P101_TRACK_EXEC_FAILURE(env, path);
        P101_ERROR_RAISE_ERRNO(err, actual_error);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_execve(const struct p101_env *env, struct p101_error *err, const char *path, char *const argv[], char *const envp[])
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    P101_TRACK_EXEC(env, path);
    errno   = 0;
    ret_val = execve(path, argv, envp);

    if(ret_val == -1)
    {
        int actual_error;

        actual_error = errno;
        P101_TRACK_EXEC_FAILURE(env, path);
        P101_ERROR_RAISE_ERRNO(err, actual_error);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_execvp(const struct p101_env *env, struct p101_error *err, const char *file, char *const argv[])
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    P101_TRACK_EXEC(env, file);
    errno   = 0;
    ret_val = execvp(file, argv);

    if(ret_val == -1)
    {
        int actual_error;

        actual_error = errno;
        P101_TRACK_EXEC_FAILURE(env, file);
        P101_ERROR_RAISE_ERRNO(err, actual_error);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_faccessat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int amode, int flag)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = faccessat(fd, path, amode, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_fchdir(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = fchdir(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_fchown(const struct p101_env *env, struct p101_error *err, int fildes, uid_t owner, gid_t group)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = fchown(fildes, owner, group);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_fchownat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, uid_t owner, gid_t group, int flag)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = fchownat(fd, path, owner, group, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_fork(const struct p101_env *env, struct p101_error *err)
{
    pid_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = fork();

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else if(ret_val == 0)
    {
        p101_env_after_fork_child(env);
    }
    else if(ret_val > 0)
    {
        pid_t child_pid;
        pid_t parent_pid;

        parent_pid = p101_getpid(env);
        child_pid  = ret_val;
        P101_TRACK_FORK(env, parent_pid, child_pid);
    }

    if(ret_val != 0)
    {
        P101_TRACE_EXIT(env);
    }
    return ret_val;
}

long p101_fpathconf(const struct p101_env *env, struct p101_error *err, int fildes, int name)
{
    long ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = fpathconf(fildes, name);

    if(ret_val == -1 && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_ftruncate(const struct p101_env *env, struct p101_error *err, int fildes, off_t length)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = ftruncate(fildes, length);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

char *p101_getcwd(const struct p101_env *env, struct p101_error *err, char *buf, size_t size)
{
    char *ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = getcwd(buf, size);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

gid_t p101_getegid(const struct p101_env *env)
{
    gid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getegid();

    P101_TRACE_EXIT(env);
    return ret_val;
}

uid_t p101_geteuid(const struct p101_env *env)
{
    uid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = geteuid();

    P101_TRACE_EXIT(env);
    return ret_val;
}

gid_t p101_getgid(const struct p101_env *env)
{
    gid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getgid();

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_getgroups(const struct p101_env *env, struct p101_error *err, int gidsetsize, gid_t grouplist[])
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = getgroups(gidsetsize, grouplist);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_gethostname(const struct p101_env *env, struct p101_error *err, char *name, size_t namelen)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = gethostname(name, namelen);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_getlogin_r(const struct p101_env *env, struct p101_error *err, char *name, size_t namesize)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = getlogin_r(name, namesize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_getopt(const struct p101_env *env, int argc, char *const argv[], const char *optstring)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getopt(argc, argv, optstring);

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_getpgid(const struct p101_env *env, struct p101_error *err, pid_t pid)
{
    pid_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = getpgid(pid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_getpgrp(const struct p101_env *env)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpgrp();

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_getpid(const struct p101_env *env)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpid();

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_getppid(const struct p101_env *env)
{
    pid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getppid();

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_getsid(const struct p101_env *env, struct p101_error *err, pid_t pid)
{
    pid_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = getsid(pid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

uid_t p101_getuid(const struct p101_env *env)
{
    uid_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getuid();

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_isatty(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = isatty(fildes);

    if(ret_val == 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno == 0 ? ENOTTY : errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_lchown(const struct p101_env *env, struct p101_error *err, const char *path, uid_t owner, gid_t group)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = lchown(path, owner, group);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_link(const struct p101_env *env, struct p101_error *err, const char *path1, const char *path2)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = link(path1, path2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_linkat(const struct p101_env *env, struct p101_error *err, int fd1, const char *path1, int fd2, const char *path2, int flag)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = linkat(fd1, path1, fd2, path2, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

off_t p101_lseek(const struct p101_env *env, struct p101_error *err, int fildes, off_t offset, int whence)
{
    off_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, (off_t)-1);
    errno   = 0;
    ret_val = lseek(fildes, offset, whence);

    if(ret_val == (off_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

long p101_pathconf(const struct p101_env *env, struct p101_error *err, const char *path, int name)
{
    long ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = pathconf(path, name);

    if(ret_val == -1 && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pause(const struct p101_env *env)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pause();

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pipe(const struct p101_env *env, struct p101_error *err, int fildes[2])
{
    int ret_val;
    int fault;

    P101_TRACE(env);
    fault = p101_env_check_fault(env, "pipe");

    if(fault != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, fault);
        P101_TRACE_EXIT(env);

        return -1;
    }

    errno   = 0;
    ret_val = pipe(fildes);    // NOLINT(android-cloexec-pipe)

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        /* Both ends are descriptors, and both have to be closed -- the
         * half-closed pipe is a favourite student bug. */
        P101_TRACK_OPEN(env, fildes[0]);
        P101_TRACK_OPEN(env, fildes[1]);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}

ssize_t p101_pread(const struct p101_env *env, struct p101_error *err, int fildes, void *buf, size_t nbyte, off_t offset)
{
    ssize_t                      ret_val;
    struct p101_env_fault_action fault;

    P101_TRACE(env);
    if(p101_env_check_fault_action(env, "pread", &fault))
    {
        if(fault.kind == P101_ENV_FAULT_ERROR)
        {
            P101_ERROR_RAISE_ERRNO(err, fault.errnum);
            P101_TRACE_EXIT(env);
            return -1;
        }
        nbyte = p101_posix_short_count(nbyte, fault.amount);
    }
    errno   = 0;
    ret_val = pread(fildes, buf, nbyte, offset);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

ssize_t p101_pwrite(const struct p101_env *env, struct p101_error *err, int fildes, const void *buf, size_t nbyte, off_t offset)
{
    ssize_t                      ret_val;
    struct p101_env_fault_action fault;

    P101_TRACE(env);
    if(p101_env_check_fault_action(env, "pwrite", &fault))
    {
        if(fault.kind == P101_ENV_FAULT_ERROR)
        {
            P101_ERROR_RAISE_ERRNO(err, fault.errnum);
            P101_TRACE_EXIT(env);
            return -1;
        }
        nbyte = p101_posix_short_count(nbyte, fault.amount);
    }
    errno   = 0;
    ret_val = pwrite(fildes, buf, nbyte, offset);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

ssize_t p101_read(const struct p101_env *env, struct p101_error *err, int fildes, void *buf, size_t nbyte)
{
    ssize_t                      ret_val;
    struct p101_env_fault_action fault;

    P101_TRACE(env);
    if(p101_env_check_fault_action(env, "read", &fault))
    {
        if(fault.kind == P101_ENV_FAULT_ERROR)
        {
            P101_ERROR_RAISE_ERRNO(err, fault.errnum);
            P101_TRACE_EXIT(env);
            return -1;
        }
        nbyte = p101_posix_short_count(nbyte, fault.amount);
    }

    errno   = 0;
    ret_val = read(fildes, buf, nbyte);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}

ssize_t p101_readlink(const struct p101_env *env, struct p101_error *err, const char *restrict path, char *restrict buf, size_t bufsize)
{
    ssize_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, (ssize_t)-1);
    errno   = 0;
    ret_val = readlink(path, buf, bufsize);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

ssize_t p101_readlinkat(const struct p101_env *env, struct p101_error *err, int fd, const char *restrict path, char *restrict buf, size_t bufsize)
{
    ssize_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, (ssize_t)-1);
    errno   = 0;
    ret_val = readlinkat(fd, path, buf, bufsize);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_rmdir(const struct p101_env *env, struct p101_error *err, const char *path)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = rmdir(path);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_setegid(const struct p101_env *env, struct p101_error *err, gid_t gid)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = setegid(gid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_seteuid(const struct p101_env *env, struct p101_error *err, uid_t uid)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = seteuid(uid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_setgid(const struct p101_env *env, struct p101_error *err, gid_t gid)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = setgid(gid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_setpgid(const struct p101_env *env, struct p101_error *err, pid_t pid, pid_t pgid)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = setpgid(pid, pgid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_setsid(const struct p101_env *env, struct p101_error *err)
{
    pid_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = setsid();

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_setuid(const struct p101_env *env, struct p101_error *err, uid_t uid)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = setuid(uid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

unsigned p101_sleep(const struct p101_env *env, unsigned seconds)
{
    unsigned ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = sleep(seconds);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_symlink(const struct p101_env *env, struct p101_error *err, const char *path1, const char *path2)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = symlink(path1, path2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_symlinkat(const struct p101_env *env, struct p101_error *err, const char *path1, int fd, const char *path2)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = symlinkat(path1, fd, path2);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

long p101_sysconf(const struct p101_env *env, struct p101_error *err, int name)
{
    long ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = sysconf(name);

    if(ret_val == -1 && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

pid_t p101_tcgetpgrp(const struct p101_env *env, struct p101_error *err, int fildes)
{
    pid_t ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = tcgetpgrp(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_tcsetpgrp(const struct p101_env *env, struct p101_error *err, int fildes, pid_t pgid_id)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = tcsetpgrp(fildes, pgid_id);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_truncate(const struct p101_env *env, struct p101_error *err, const char *path, off_t length)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = truncate(path, length);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_ttyname_r(const struct p101_env *env, struct p101_error *err, int fildes, char *name, size_t namesize)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN_CODE(env, err);
    errno   = 0;
    ret_val = ttyname_r(fildes, name, namesize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_unlink(const struct p101_env *env, struct p101_error *err, const char *path)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = unlink(path);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_unlinkat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int flag)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = unlinkat(fd, path, flag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

ssize_t p101_write(const struct p101_env *env, struct p101_error *err, int fildes, const void *buf, size_t nbyte)
{
    ssize_t                      ret_val;
    struct p101_env_fault_action fault;

    P101_TRACE(env);
    if(p101_env_check_fault_action(env, "write", &fault))
    {
        if(fault.kind == P101_ENV_FAULT_ERROR)
        {
            P101_ERROR_RAISE_ERRNO(err, fault.errnum);
            P101_TRACE_EXIT(env);
            return -1;
        }
        nbyte = p101_posix_short_count(nbyte, fault.amount);
    }

    errno   = 0;
    ret_val = write(fildes, buf, nbyte);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}
