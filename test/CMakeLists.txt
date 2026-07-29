cmake_minimum_required(VERSION 3.14)
project(p101_posix_tests C CXX)
enable_testing()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(P101_TEST_COVERAGE "Instrument the tests for coverage" OFF)
set(P101_TEST_COVERAGE_FLAGS "")
if(P101_TEST_COVERAGE)
    set(P101_TEST_COVERAGE_FLAGS --coverage)
endif()

set(P101_PUBLIC_INCLUDE_DIRS "" CACHE STRING "Extra p101 include dirs")
set(P101_PUBLIC_LINK_DIRS "" CACHE STRING "Extra p101 link dirs")
separate_arguments(P101_PUBLIC_INCLUDE_DIRS_LIST NATIVE_COMMAND "${P101_PUBLIC_INCLUDE_DIRS}")
separate_arguments(P101_PUBLIC_LINK_DIRS_LIST NATIVE_COMMAND "${P101_PUBLIC_LINK_DIRS}")

if(P101_PUBLIC_LINK_DIRS_LIST)
    unset(P101_POSIX_LIBRARY CACHE)
    unset(P101_C_LIBRARY CACHE)
    unset(P101_ENV_LIBRARY CACHE)
    unset(P101_ERROR_LIBRARY CACHE)
    find_library(P101_POSIX_LIBRARY NAMES p101_posix PATHS ${P101_PUBLIC_LINK_DIRS_LIST} NO_DEFAULT_PATH)
    find_library(P101_C_LIBRARY NAMES p101_c PATHS ${P101_PUBLIC_LINK_DIRS_LIST} NO_DEFAULT_PATH)
    find_library(P101_ENV_LIBRARY NAMES p101_env PATHS ${P101_PUBLIC_LINK_DIRS_LIST} NO_DEFAULT_PATH)
    find_library(P101_ERROR_LIBRARY NAMES p101_error PATHS ${P101_PUBLIC_LINK_DIRS_LIST} NO_DEFAULT_PATH)
else()
    find_library(P101_POSIX_LIBRARY NAMES p101_posix)
    find_library(P101_C_LIBRARY NAMES p101_c)
    find_library(P101_ENV_LIBRARY NAMES p101_env)
    find_library(P101_ERROR_LIBRARY NAMES p101_error)
endif()
if(NOT P101_POSIX_LIBRARY OR NOT P101_C_LIBRARY OR NOT P101_ENV_LIBRARY OR NOT P101_ERROR_LIBRARY)
    message(FATAL_ERROR "Could not find the p101_posix, p101_c, p101_env, and p101_error test libraries")
endif()

set(P101_TEST_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
        ${P101_PUBLIC_INCLUDE_DIRS_LIST}
)
set(P101_TEST_LIBRARIES
        "${P101_POSIX_LIBRARY}"
        "${P101_C_LIBRARY}"
        "${P101_ENV_LIBRARY}"
        "${P101_ERROR_LIBRARY}"
)

add_executable(test_lib_posix test_lib_posix.c)
target_include_directories(test_lib_posix PRIVATE ${P101_TEST_INCLUDE_DIRS})
target_compile_definitions(test_lib_posix PRIVATE _POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)
if(APPLE)
    target_compile_definitions(test_lib_posix PRIVATE _DARWIN_C_SOURCE)
endif()
target_compile_options(test_lib_posix PRIVATE ${P101_TEST_COVERAGE_FLAGS})
target_link_options(test_lib_posix PRIVATE ${P101_TEST_COVERAGE_FLAGS})
target_link_libraries(test_lib_posix PRIVATE ${P101_TEST_LIBRARIES})
add_test(NAME test_lib_posix COMMAND test_lib_posix)

add_executable(test_headers_c test_headers.c)
target_include_directories(test_headers_c PRIVATE ${P101_TEST_INCLUDE_DIRS})
target_compile_definitions(test_headers_c PRIVATE _POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)
target_link_libraries(test_headers_c PRIVATE ${P101_TEST_LIBRARIES})
add_test(NAME test_headers_c COMMAND test_headers_c)

add_executable(test_headers_cxx test_headers.cpp)
target_include_directories(test_headers_cxx PRIVATE ${P101_TEST_INCLUDE_DIRS})
target_compile_definitions(test_headers_cxx PRIVATE _POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)
target_link_libraries(test_headers_cxx PRIVATE ${P101_TEST_LIBRARIES})
add_test(NAME test_headers_cxx COMMAND test_headers_cxx)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(test_lib_posix PRIVATE -Wall -Wextra -Werror -pedantic-errors)
    target_compile_options(test_headers_c PRIVATE -Wall -Wextra -Werror -pedantic-errors)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(test_headers_cxx PRIVATE -Wall -Wextra -Werror -pedantic-errors)
endif()
