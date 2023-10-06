#ifndef LIBP101_POSIX_P101_UNISTD_H
#define LIBP101_POSIX_P101_UNISTD_H

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

#include <p101_env/env.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int            p101_access(const struct p101_env *env, struct p101_error *err, const char *path, int amode);
    unsigned       p101_alarm(const struct p101_env *env, unsigned seconds);
    int            p101_chdir(const struct p101_env *env, struct p101_error *err, const char *path);
    int            p101_chown(const struct p101_env *env, struct p101_error *err, const char *path, uid_t owner, gid_t group);
    int            p101_close(const struct p101_env *env, struct p101_error *err, int fildes);
    size_t         p101_confstr(const struct p101_env *env, struct p101_error *err, int name, char *buf, size_t len);
    int            p101_dup(const struct p101_env *env, struct p101_error *err, int fildes);
    int            p101_dup2(const struct p101_env *env, struct p101_error *err, int fildes, int fildes2);
    _Noreturn void p101__exit(const struct p101_env *env, int status);
    int            p101_execv(const struct p101_env *env, struct p101_error *err, const char *path, char *const argv[]);
    int            p101_execve(const struct p101_env *env, struct p101_error *err, const char *path, char *const argv[], char *const envp[]);
    int            p101_execvp(const struct p101_env *env, struct p101_error *err, const char *file, char *const argv[]);
    int            p101_faccessat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int amode, int flag);
    int            p101_fchdir(const struct p101_env *env, struct p101_error *err, int fildes);
    int            p101_fchown(const struct p101_env *env, struct p101_error *err, int fildes, uid_t owner, gid_t group);
    int            p101_fchownat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, uid_t owner, gid_t group, int flag);
    pid_t          p101_fork(const struct p101_env *env, struct p101_error *err);
    long           p101_fpathconf(const struct p101_env *env, struct p101_error *err, int fildes, int name);
    int            p101_ftruncate(const struct p101_env *env, struct p101_error *err, int fildes, off_t length);
    char          *p101_getcwd(const struct p101_env *env, struct p101_error *err, char *buf, size_t size);
    gid_t          p101_getegid(const struct p101_env *env);
    uid_t          p101_geteuid(const struct p101_env *env);
    gid_t          p101_getgid(const struct p101_env *env);
    int            p101_getgroups(const struct p101_env *env, struct p101_error *err, int gidsetsize, gid_t grouplist[]);
    int            p101_gethostname(const struct p101_env *env, struct p101_error *err, char *name, size_t namelen);
    int            p101_getlogin_r(const struct p101_env *env, struct p101_error *err, char *name, size_t namesize);
    int            p101_getopt(const struct p101_env *env, int argc, char *const argv[], const char *optstring);
    pid_t          p101_getpgid(const struct p101_env *env, struct p101_error *err, pid_t pid);
    pid_t          p101_getpgrp(const struct p101_env *env);
    pid_t          p101_getpid(const struct p101_env *env);
    pid_t          p101_getppid(const struct p101_env *env);
    pid_t          p101_getsid(const struct p101_env *env, struct p101_error *err, pid_t pid);
    uid_t          p101_getuid(const struct p101_env *env);
    int            p101_isatty(const struct p101_env *env, struct p101_error *err, int fildes);
    int            p101_lchown(const struct p101_env *env, struct p101_error *err, const char *path, uid_t owner, gid_t group);
    int            p101_link(const struct p101_env *env, struct p101_error *err, const char *path1, const char *path2);
    int            p101_linkat(const struct p101_env *env, struct p101_error *err, int fd1, const char *path1, int fd2, const char *path2, int flag);
    off_t          p101_lseek(const struct p101_env *env, struct p101_error *err, int fildes, off_t offset, int whence);
    long           p101_pathconf(const struct p101_env *env, struct p101_error *err, const char *path, int name);
    int            p101_pause(const struct p101_env *env, struct p101_error *err);
    int            p101_pipe(const struct p101_env *env, struct p101_error *err, int fildes[2]);
    ssize_t        p101_pread(const struct p101_env *env, struct p101_error *err, int fildes, void *buf, size_t nbyte, off_t offset);
    ssize_t        p101_pwrite(const struct p101_env *env, struct p101_error *err, int fildes, const void *buf, size_t nbyte, off_t offset);
    ssize_t        p101_read(const struct p101_env *env, struct p101_error *err, int fildes, void *buf, size_t nbyte);
    ssize_t        p101_readlink(const struct p101_env *env, struct p101_error *err, const char *restrict path, char *restrict buf, size_t bufsize);
    ssize_t        p101_readlinkat(const struct p101_env *env, struct p101_error *err, int fd, const char *restrict path, char *restrict buf, size_t bufsize);
    int            p101_rmdir(const struct p101_env *env, struct p101_error *err, const char *path);
    int            p101_setegid(const struct p101_env *env, struct p101_error *err, gid_t gid);
    int            p101_seteuid(const struct p101_env *env, struct p101_error *err, uid_t uid);
    int            p101_setgid(const struct p101_env *env, struct p101_error *err, gid_t gid);
    int            p101_setpgid(const struct p101_env *env, struct p101_error *err, pid_t pid, pid_t pgid);
    pid_t          p101_setsid(const struct p101_env *env, struct p101_error *err);
    int            p101_setuid(const struct p101_env *env, struct p101_error *err, uid_t uid);
    unsigned       p101_sleep(const struct p101_env *env, unsigned seconds);
    int            p101_symlink(const struct p101_env *env, struct p101_error *err, const char *path1, const char *path2);
    int            p101_symlinkat(const struct p101_env *env, struct p101_error *err, const char *path1, int fd, const char *path2);
    long           p101_sysconf(const struct p101_env *env, struct p101_error *err, int name);
    pid_t          p101_tcgetpgrp(const struct p101_env *env, struct p101_error *err, int fildes);
    int            p101_tcsetpgrp(const struct p101_env *env, struct p101_error *err, int fildes, pid_t pgid_id);
    int            p101_truncate(const struct p101_env *env, struct p101_error *err, const char *path, off_t length);
    int            p101_ttyname_r(const struct p101_env *env, struct p101_error *err, int fildes, char *name, size_t namesize);
    int            p101_unlink(const struct p101_env *env, struct p101_error *err, const char *path);
    int            p101_unlinkat(const struct p101_env *env, struct p101_error *err, int fd, const char *path, int flag);
    ssize_t        p101_write(const struct p101_env *env, struct p101_error *err, int fildes, const void *buf, size_t nbyte);

#ifdef __cplusplus
}
#endif

// unsafe
// char *p101_getlogin(const struct p101_env *env, struct p101_error *err);
// char *p101_ttyname(const struct p101_env *env, struct p101_error *err, int fildes);

// not on macOS
// int p101_fexecve(const struct p101_env *env, struct p101_error *err, int fd, char *const argv[], char *const envp[]);

#endif    // LIBP101_POSIX_P101_UNISTD_H
