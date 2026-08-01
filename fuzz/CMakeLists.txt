cmake_minimum_required(VERSION 3.14)
project(p101_posix_fuzz C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Fuzzing requires clang with libFuzzer")
endif()

set(P101_PUBLIC_INCLUDE_DIRS "" CACHE STRING "Extra p101 include dirs")
set(P101_PUBLIC_LINK_DIRS "" CACHE STRING "Extra p101 link dirs")
separate_arguments(P101_PUBLIC_INCLUDE_DIRS_LIST NATIVE_COMMAND "${P101_PUBLIC_INCLUDE_DIRS}")
separate_arguments(P101_PUBLIC_LINK_DIRS_LIST NATIVE_COMMAND "${P101_PUBLIC_LINK_DIRS}")

if(P101_PUBLIC_LINK_DIRS_LIST)
    find_library(P101_C_LIBRARY NAMES p101_c PATHS ${P101_PUBLIC_LINK_DIRS_LIST} NO_DEFAULT_PATH)
else()
    find_library(P101_C_LIBRARY NAMES p101_c)
endif()
if(NOT P101_C_LIBRARY)
    message(FATAL_ERROR "Could not find the p101_c fuzz library")
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/../config.cmake")
set(P101_POSIX_FUZZ_SOURCES "")
foreach(source IN LISTS p101_posix_SOURCES)
    list(APPEND P101_POSIX_FUZZ_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../${source}")
endforeach()

set(P101_FUZZ_FLAGS -fsanitize=fuzzer,address,undefined -g -O1)

add_executable(fuzz
        fuzz_lib_posix.c
        ${P101_POSIX_FUZZ_SOURCES}
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_tool_event/src/record.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_tool_event/src/event.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_env/src/env.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_error/src/check.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_error/src/error.c"
)
target_include_directories(fuzz PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_env/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib_error/include"
        ${P101_PUBLIC_INCLUDE_DIRS_LIST}
)
target_compile_definitions(fuzz PRIVATE _POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)
if(APPLE)
    target_compile_definitions(fuzz PRIVATE _DARWIN_C_SOURCE)
endif()
target_compile_options(fuzz PRIVATE ${P101_FUZZ_FLAGS})
target_link_options(fuzz PRIVATE ${P101_FUZZ_FLAGS})
target_link_libraries(fuzz PRIVATE
        "${P101_C_LIBRARY}"
        iconv
)
