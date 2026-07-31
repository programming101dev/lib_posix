# lib_posix Repository Guide (retired)

This standards-based aggregate has been replaced by the functional `lib_*`
repositories listed in `scripts/repos.txt`. It is retained only as migration
history and is no longer part of the active build, install, or CI graph.

Welcome to the `lib_posix` repository — POSIX utilities, part of the Programming 101 C library collection. This guide will help you set up, build, and install the library.

## **Table of Contents**

1. [Cloning the Repository](#cloning-the-repository)
2. [Prerequisites](#prerequisites)
3. [Configuring the Build](#configuring-the-build)
4. [Building](#building)
5. [Testing](#testing)
6. [Installing](#installing)
7. [Adding or Removing Files](#adding-or-removing-files)

## **Cloning the Repository**

Clone the repository using the following command:

```bash
git clone https://github.com/programming101dev/lib_posix.git
```

Navigate to the cloned directory:

```bash
cd lib_posix
```

Ensure the scripts are executable:

```bash
chmod +x *.sh
```

## **Prerequisites**

To ensure you have all of the required tools installed, run:

```bash
./check-env.sh
```

If you are missing tools follow these [instructions](https://docs.google.com/document/d/1ZPqlPD1mie5iwJ2XAcNGz7WeA86dTLerFXs9sAuwCco/edit?usp=drive_link). If something still looks wrong, `./doctor.sh` reports what actually works on this machine for this project.

## **Configuring the Build**

Tell CMake which compiler you want to use:

```bash
./change-compiler.sh -c <compiler>
```

To see the list of possible compilers:

```bash
cat supported_c_compilers.txt
```

Run it again any time to switch compilers; each compiler configures into its own build directory (e.g. `build-clang`, `build-gcc-15`).

## **Building**

To build the library run:

```bash
./build.sh
```

This compiles through the strict analysis pipeline: the clang-format check, clang-tidy, cppcheck, the Clang static analyzer, and hundreds of warnings under `-Werror`. `./build.sh -f` applies the formatter and tidy fixes in place.

## **Testing**

`./check.sh` is the one command to run before you submit: the format check, the strict build, the tests, and a short fuzz smoke run, with a single PASS/FAIL at the end.
The repository has contract tests for error sentinels, resource events, fault
injection, balanced call tracing, and C/C++ public-header compatibility:

```bash
./test.sh
```

When a libFuzzer-capable Clang is installed, the bounded smoke harness exercises
regular expressions, filename matching, word expansion with command execution
disabled, address parsing, and multibyte conversion:

```bash
./fuzz.sh -t 30
```

These are executable regression checks, not proof of correctness. Fuzzing only
covers inputs reached during its time budget.

## Wrapper contract

Every wrapper emits a call-entry and call-exit event through `p101_env`.
Wrappers that accept `struct p101_error *` also honor the environment's fault
injector while preserving the native interface's return convention. Native
statuses that describe an expected outcome—such as end-of-file, `EBUSY` from a
try-lock, `ETIMEDOUT`, or `EAGAIN` from `sem_trywait`—are returned without
inventing an application error.

The generic wrapper trace records the function name and source location, not
typed argument or result values. Code that has a safe, useful textual
representation for those values can opt into payload logging with
`P101_CALL_ENTER` and `P101_CALL_EXIT`; strings, buffers, credentials, and
opaque handles are deliberately not formatted automatically.

Descriptor-producing wrappers emit open/close events where the underlying
descriptor is observable. Allocation-producing interfaces such as `wcsdup`,
`getline`, `getdelim`, and `scandir` emit allocation events. The observations
are limited to calls routed through `p101_*`; direct libc calls and work done
inside third-party libraries are not visible. The current resource schema
models descriptors and heap allocations. Opaque POSIX lifetimes such as locale,
catalog, iconv, dynamic-loader, regular-expression, and word-expansion handles
still appear in the call trace, but are not classified as leak-checkable
resources.

`sigsetjmp` is intentionally not wrapped. It must execute directly in the stack
frame that will receive the corresponding `siglongjmp`; a normal function
wrapper cannot preserve that contract. Call `sigsetjmp` directly and use
`p101_siglongjmp` for the jump.

## Deliberately omitted interfaces

The public headers contain only APIs implemented on every supported platform:
macOS, Linux, and FreeBSD. Platform-specific or unsafe/obsolete interfaces are
omitted rather than left as commented declarations. Notable omissions include
the legacy non-reentrant password/group/network database lookups,
`readdir_r`, `ctermid`, unnamed POSIX semaphore operations that macOS
deprecates, POSIX timers absent from macOS, and locale-specific wide-string
comparisons absent from FreeBSD.

## **Installing**

To install the library run:

```bash
./install.sh
```

You may need to run it via sudo, or give the user account access to the install directories. `./uninstall.sh` removes it again.

## **Adding or Removing Files**

The `CMakeLists.txt` is fixed and shared across every repository — do not edit it. When you add or remove a source or header, edit the lists in `config.cmake` (`p101_posix_SOURCES`, `p101_posix_HEADERS`, and `p101_posix_LINK_LIBRARIES`), then re-configure and build:

```bash
./change-compiler.sh -c <compiler>
./build.sh
```
