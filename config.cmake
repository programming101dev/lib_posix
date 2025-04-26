# Project metadata
set(PROJECT_NAME "p101_posix")
set(PROJECT_VERSION "0.0.1")
set(PROJECT_DESCRIPTION "POSIX utilities")
set(PROJECT_LANGUAGE "C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Define library targets
set(LIBRARY_TARGETS p101_posix)

# Source files for the library
set(p101_posix_SOURCES
        src/aio.c
        src/ctype.c
        src/dirent.c
        src/dlfcn.c
        src/fcntl.c
        src/fnmatch.c
        src/glob.c
        src/grp.c
        src/iconv.c
        src/langinfo.c
        src/locale.c
        src/netdb.c
        src/nl_types.c
        src/poll.c
        src/pthread.c
        src/pwd.c
        src/regex.c
        src/sched.c
        src/semaphore.c
        src/setjmp.c
        src/signal.c
        src/stdio.c
        src/stdlib.c
        src/string.c
        src/strings.c
        src/termios.c
        src/time.c
        src/unistd.c
        src/wchar.c
        src/wctype.c
        src/wordexp.c
        src/arpa/inet.c
        src/net/if.c
        src/sys/mman.c
        src/sys/select.c
        src/sys/socket.c
        src/sys/stat.c
        src/sys/statvfs.c
        src/sys/times.c
        src/sys/utsname.c
        src/sys/wait.c
)

# Header files for installation, merging all headers into one list
set(p101_posix_HEADERS
        include/p101_posix/p101_aio.h
        include/p101_posix/p101_ctype.h
        include/p101_posix/p101_dirent.h
        include/p101_posix/p101_dlfcn.h
        include/p101_posix/p101_fcntl.h
        include/p101_posix/p101_fnmatch.h
        include/p101_posix/p101_glob.h
        include/p101_posix/p101_grp.h
        include/p101_posix/p101_iconv.h
        include/p101_posix/p101_langinfo.h
        include/p101_posix/p101_locale.h
        include/p101_posix/p101_netdb.h
        include/p101_posix/p101_nl_types.h
        include/p101_posix/p101_poll.h
        include/p101_posix/p101_pthread.h
        include/p101_posix/p101_pwd.h
        include/p101_posix/p101_regex.h
        include/p101_posix/p101_sched.h
        include/p101_posix/p101_semaphore.h
        include/p101_posix/p101_setjmp.h
        include/p101_posix/p101_signal.h
        include/p101_posix/p101_stdio.h
        include/p101_posix/p101_stdlib.h
        include/p101_posix/p101_string.h
        include/p101_posix/p101_strings.h
        include/p101_posix/p101_termios.h
        include/p101_posix/p101_time.h
        include/p101_posix/p101_unistd.h
        include/p101_posix/p101_wchar.h
        include/p101_posix/p101_wctype.h
        include/p101_posix/p101_wordexp.h
        include/p101_posix/arpa/p101_inet.h
        include/p101_posix/net/p101_if.h
        include/p101_posix/sys/p101_mman.h
        include/p101_posix/sys/p101_select.h
        include/p101_posix/sys/p101_socket.h
        include/p101_posix/sys/p101_stat.h
        include/p101_posix/sys/p101_statvfs.h
        include/p101_posix/sys/p101_times.h
        include/p101_posix/sys/p101_utsname.h
        include/p101_posix/sys/p101_wait.h
)

# Linked libraries required for this project
set(p101_posix_LINK_LIBRARIES
        p101_error
        p101_env
        p101_c
        iconv
)
