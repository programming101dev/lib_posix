cmake_minimum_required(VERSION 3.10)
project(p101_posix
    VERSION 0.0.1
    DESCRIPTION ""
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Source files for the library
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/aio.c
    ${CMAKE_SOURCE_DIR}/src/ctype.c
    ${CMAKE_SOURCE_DIR}/src/dirent.c
    ${CMAKE_SOURCE_DIR}/src/dlfcn.c
    ${CMAKE_SOURCE_DIR}/src/fcntl.c
    ${CMAKE_SOURCE_DIR}/src/fnmatch.c
    ${CMAKE_SOURCE_DIR}/src/glob.c
    ${CMAKE_SOURCE_DIR}/src/grp.c
    ${CMAKE_SOURCE_DIR}/src/iconv.c
    ${CMAKE_SOURCE_DIR}/src/langinfo.c
    ${CMAKE_SOURCE_DIR}/src/locale.c
    ${CMAKE_SOURCE_DIR}/src/netdb.c
    ${CMAKE_SOURCE_DIR}/src/nl_types.c
    ${CMAKE_SOURCE_DIR}/src/poll.c
    ${CMAKE_SOURCE_DIR}/src/pthread.c
    ${CMAKE_SOURCE_DIR}/src/pwd.c
    ${CMAKE_SOURCE_DIR}/src/regex.c
    ${CMAKE_SOURCE_DIR}/src/sched.c
    ${CMAKE_SOURCE_DIR}/src/semaphore.c
    ${CMAKE_SOURCE_DIR}/src/setjmp.c
    ${CMAKE_SOURCE_DIR}/src/signal.c
    ${CMAKE_SOURCE_DIR}/src/stdio.c
    ${CMAKE_SOURCE_DIR}/src/stdlib.c
    ${CMAKE_SOURCE_DIR}/src/string.c
    ${CMAKE_SOURCE_DIR}/src/strings.c
    ${CMAKE_SOURCE_DIR}/src/termios.c
    ${CMAKE_SOURCE_DIR}/src/time.c
    ${CMAKE_SOURCE_DIR}/src/unistd.c
    ${CMAKE_SOURCE_DIR}/src/wchar.c
    ${CMAKE_SOURCE_DIR}/src/wctype.c
    ${CMAKE_SOURCE_DIR}/src/wordexp.c
    ${CMAKE_SOURCE_DIR}/src/arpa/inet.c
    ${CMAKE_SOURCE_DIR}/src/net/if.c
    ${CMAKE_SOURCE_DIR}/src/sys/mman.c
    ${CMAKE_SOURCE_DIR}/src/sys/select.c
    ${CMAKE_SOURCE_DIR}/src/sys/socket.c
    ${CMAKE_SOURCE_DIR}/src/sys/stat.c
    ${CMAKE_SOURCE_DIR}/src/sys/statvfs.c
    ${CMAKE_SOURCE_DIR}/src/sys/times.c
    ${CMAKE_SOURCE_DIR}/src/sys/utsname.c
    ${CMAKE_SOURCE_DIR}/src/sys/wait.c
)

# Define the list of header files to install
set(HEADER_LIST
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_aio.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_ctype.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_dirent.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_dlfcn.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_fcntl.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_fnmatch.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_glob.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_grp.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_iconv.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_langinfo.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_locale.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_netdb.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_nl_types.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_poll.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_pthread.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_pwd.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_regex.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_sched.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_semaphore.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_setjmp.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_signal.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_stdio.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_stdlib.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_string.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_strings.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_termios.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_time.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_unistd.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_wchar.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_wctype.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_ctype.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/p101_wordexp.h
)

set(HEADER_LIST_ARPA 
    ${CMAKE_SOURCE_DIR}/include/p101_posix/arpa/p101_inet.h
)

set(HEADER_LIST_NET 
    ${CMAKE_SOURCE_DIR}/include/p101_posix/net/p101_if.h
)

set(HEADER_LIST_SYS
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_mman.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_select.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_socket.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_stat.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_statvfs.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_times.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_utsname.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/p101_wait.h
)

# Build the shared library
add_library(p101_posix SHARED ${SOURCES})
target_include_directories(p101_posix PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(p101_posix PRIVATE /usr/local/include)

# Extract the compiler name without the path
get_filename_component(COMPILER_NAME "${CMAKE_C_COMPILER}" NAME)

function(split_string_into_list _input_string _output_list)
    string(REGEX REPLACE "[ ]+" ";" _split_list "${_input_string}")
    set(${_output_list} ${_split_list} PARENT_SCOPE)
endfunction()

# Import warning_flags.txt
file(STRINGS "${CMAKE_SOURCE_DIR}/../flags/${COMPILER_NAME}/warning_flags.txt" WARNING_FLAGS_STRING)
split_string_into_list("${WARNING_FLAGS_STRING}" WARNING_FLAGS_LIST)

# Import analyzer_flags.txt
file(STRINGS "${CMAKE_SOURCE_DIR}/../flags/${COMPILER_NAME}/analyzer_flags.txt" ANALYZER_FLAGS_STRING)
split_string_into_list("${ANALYZER_FLAGS_STRING}" ANALYZER_FLAGS_LIST)

# Import debug_flags.txt
file(STRINGS "${CMAKE_SOURCE_DIR}/../flags/${COMPILER_NAME}/debug_flags.txt" DEBUG_FLAGSSTRING)
split_string_into_list("${DEBUG_FLAGS_STRING}" DEBUG_FLAGS_LIST)

# Import sanitizer_flags.txt
file(STRINGS "${CMAKE_SOURCE_DIR}/../flags/${COMPILER_NAME}/sanitizer_flags.txt" SANITIZER_FLAGS_STRING)
split_string_into_list("${SANITIZER_FLAGS_STRING}" SANITIZER_FLAGS_LIST)

# Check if the system uses 64-bit libraries
get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)

# Set the library suffix based on whether it's 64-bit or not
if ("${LIB64}" STREQUAL "TRUE")
    set(LIBSUFFIX 64)
else()
    set(LIBSUFFIX "")
endif()

target_link_directories(p101_posix PRIVATE /usr/local/lib${LIBSUFFIX})

# Link libraries
target_link_libraries(p101_posix PRIVATE ${SANITIZER_FLAGS_STRING})

# Link libraries (if needed)
target_link_libraries(p101_posix PRIVATE p101_error)
target_link_libraries(p101_posix PRIVATE p101_env)
target_link_libraries(p101_posix PRIVATE p101_c)

find_library(ICONV_LIBRARY iconv)

if(ICONV_LIBRARY)
    target_link_libraries(p101_posix PRIVATE ${ICONV_LIBRARY})
endif()

# Common compiler flags
set(STANDARD_FLAGS
    -D_POSIX_C_SOURCE=200809L
    -D_XOPEN_SOURCE=700
    -D_DARWIN_C_SOURCE
    -Werror
)

# Set compiler flags for the target
target_compile_options(p101_posix PRIVATE
    ${STANDARD_FLAGS}
    ${WARNING_FLAGS_LIST}
    ${ANALYZER_FLAGS_LIST}
    ${DEBUG_FLAGS_LIST}
    ${SANITIZER_FLAGS_LIST}
)

if (NOT DEFINED CLANG_FORMAT_NAME)
    set(CLANG_FORMAT_NAME "clang-format")
endif()

if (NOT DEFINED CLANG_TIDY_NAME)
    set(CLANG_TIDY_NAME "clang-tidy")
endif()

if (NOT DEFINED CPPCHECK_NAME)
    set(CPPCHECK_NAME "cppcheck")
endif()

find_program(CLANG_FORMAT NAMES ${CLANG_FORMAT_NAME} REQUIRED)
find_program(CLANG_TIDY NAMES ${CLANG_TIDY_NAME} REQUIRED)
find_program(CPPCHECK NAMES ${CPPCHECK_NAME} REQUIRED)

# Format source files using clang-format
add_custom_target(format
    COMMAND ${CLANG_FORMAT} --style=file -i ${SOURCES} ${HEADER_LIST} ${HEADER_LIST_ARPA} ${HEADER_LIST_NET} ${HEADER_LIST_SYS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-format"
)

# Lint source files using clang-tidy
add_custom_target(lint
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ${CLANG_TIDY} ${SOURCES} ${HEADER_LIST} ${HEADER_LIST_ARPA} ${HEADER_LIST_NET} ${HEADER_LIST_SYS} -quiet --warnings-as-errors='*' -checks=*,-llvmlibc-restrict-system-libc-headers,-altera-struct-pack-align,-readability-identifier-length,-altera-unroll-loops,-cppcoreguidelines-init-variables,-cert-err33-c,-modernize-macro-to-enum,-bugprone-easily-swappable-parameters,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-altera-id-dependent-backward-branch,-concurrency-mt-unsafe,-misc-unused-parameters,-hicpp-signed-bitwise,-google-readability-todo,-cert-msc30-c,-cert-msc50-cpp,-readability-function-cognitive-complexity,-clang-analyzer-security.insecureAPI.strcpy,-cert-env33-c,-android-cloexec-accept,-clang-analyzer-security.insecureAPI.rand,-misc-include-cleaner,-llvm-header-guard -- ${CMAKE_C_FLAGS} ${STANDARD_FLAGS} -I${CMAKE_SOURCE_DIR}/include -I/usr/local/include
    COMMENT "Running clang-tidy"
)

# Add a custom target for cppcheck
add_custom_target(cppcheck
    COMMAND ${CPPCHECK} --error-exitcode=1 --force --quiet --inline-suppr --library=posix --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=readdirCalled --suppress=gethostentCalled --suppress=getnetbyaddrCalled --suppress=getnetbynameCalled --suppress=getnetentCalled --suppress=getprotobynameCalled --suppress=getprotobynumberCalled --suppress=getprotoentCalled --suppress=getservbynameCalled --suppress=getservbyportCalled --suppress=getserventCalled --suppress=ctermidCalled --suppress=constParameterPointer --suppress=unmatchedSuppression -I${CMAKE_SOURCE_DIR}/include -I/usr/local/include ${SOURCES} ${HEADER_LIST} ${HEADER_LIST_ARPA} ${HEADER_LIST_NET} ${HEADER_LIST_SYS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cppcheck"
)

# Check if CMAKE_C_COMPILER starts with "clang"
if (CMAKE_C_COMPILER MATCHES ".*/clang.*")
    # Add a custom target for clang --analyze
    add_custom_target(analysis
        COMMAND ${CMAKE_C_COMPILER} --analyze --analyzer-output text -Xclang -analyzer-checker=core --analyze -Xclang -analyzer-checker=deadcode -Xclang -analyzer-checker=security -Xclang -analyzer-disable-checker=security.insecureAPI.DeprecatedOrUnsafeBufferHandling -Xclang -analyzer-checker=unix -Xclang -analyzer-checker=unix ${CMAKE_C_FLAGS} ${STANDARD_FLAGS} -I${CMAKE_SOURCE_DIR}/include -I/usr/local/include ${SOURCES} ${HEADER_LIST} ${HEADER_LIST_ARPA} ${HEADER_LIST_NET} ${HEADER_LIST_SYS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang --analyze"
    )

    # Add a custom command to delete .gch files after the analysis
    add_custom_command(
        TARGET analysis POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/include/p101_posix/*.gch ${CMAKE_SOURCE_DIR}/include/p101_posix/arpa/*.gch ${CMAKE_SOURCE_DIR}/include/p101_posix/net/*.gch ${CMAKE_SOURCE_DIR}/include/p101_posix/sys/*.gch
        COMMENT "Removing .gch files"
    )

    # Add dependencies including 'analysis' for Clang compiler
    add_custom_target(strict
        DEPENDS p101_posix analysis lint cppcheck
        COMMENT "Running code analysis tools"
    )
else()
    # Add dependencies without 'analysis' for other compilers
    add_custom_target(strict
        DEPENDS p101_posix lint cppcheck
        COMMENT "Running code analysis tools"
    )
endif()

add_dependencies(p101_posix format)

# Set the default target to be 'strict'
add_custom_target(default_target DEPENDS strict)

# Define the installation directory for libraries
set(INSTALL_LIB_DIR lib${LIBSUFFIX} CACHE PATH "Installation directory for libraries")
mark_as_advanced(INSTALL_LIB_DIR)

set_target_properties(p101_posix PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

# Install the library target
install(TARGETS p101_posix
    LIBRARY DESTINATION ${INSTALL_LIB_DIR}
    COMPONENT library
    NAMELINK_COMPONENT development
)

# Install header files
install(FILES ${HEADER_LIST}
    DESTINATION include/p101_posix
)

install(FILES ${HEADER_LIST_ARPA}
    DESTINATION include/p101_posix/arpa
)

install(FILES ${HEADER_LIST_NET}
    DESTINATION include/p101_posix/net
)

install(FILES ${HEADER_LIST_SYS}
    DESTINATION include/p101_posix/sys
)
