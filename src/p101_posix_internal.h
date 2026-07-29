#ifndef LIBP101_POSIX_INTERNAL_H
#define LIBP101_POSIX_INTERNAL_H

#include <p101_env/env.h>
#include <p101_error/error.h>

/*
 * Fault injection is test policy carried by p101_env. Keep the mechanics
 * private and uniform so every fallible POSIX wrapper exits its trace and
 * preserves the wrapped interface's return convention.
 */
// clang-format off
#define P101_POSIX_FAULT_RETURN(env, err, failure_value)                  \
    do                                                                   \
    {                                                                    \
        int p101_posix_fault_code_;                                      \
                                                                         \
        p101_posix_fault_code_ = p101_env_check_fault((env), __func__ + 5); \
        if(p101_posix_fault_code_ != 0)                                  \
        {                                                                \
            P101_ERROR_RAISE_ERRNO((err), p101_posix_fault_code_);       \
            P101_TRACE_EXIT(env);                                        \
            return (failure_value);                                      \
        }                                                                \
    } while(0)

#define P101_POSIX_FAULT_RETURN_CODE(env, err)                            \
    do                                                                   \
    {                                                                    \
        int p101_posix_fault_code_;                                      \
                                                                         \
        p101_posix_fault_code_ = p101_env_check_fault((env), __func__ + 5); \
        if(p101_posix_fault_code_ != 0)                                  \
        {                                                                \
            P101_ERROR_RAISE_ERRNO((err), p101_posix_fault_code_);       \
            P101_TRACE_EXIT(env);                                        \
            return p101_posix_fault_code_;                               \
        }                                                                \
    } while(0)
// clang-format on

#endif
