#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([advent-of-code-cpp], [0.1.0-alpha],
    [liuxf19@163.com], [advent-of-code-cpp], [https://github.com/Timothy-Liuxf/advent-of-code-cpp])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4 third_party/autoconf-archive/m4])
AC_PROG_RANLIB

AM_INIT_AUTOMAKE([foreign subdir-objects tar-pax])

AX_INIT_CXXFLAGS
AX_CXX_COMPILE_STDCXX_EX(23, [noext], [mandatory])

# AX_APPEND_COMPILE_FLAGS([-O2 -std=c++17], [CXXFLAGS])
AX_APPEND_COMPILE_FLAGS([-Wall -Wpedantic -Wextra -Werror], [CXXFLAGS])
AX_APPEND_COMPILE_FLAGS([                                                    dnl
    -I.                                                                      dnl
    -Isrc                                                                    dnl
    -Ithird_party/tclap/include                                              dnl
], [CXXFLAGS])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
