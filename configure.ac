#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([redocx], [1.0], [Ping on GitHub])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/xml.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([XML], [libxml-2.0])
PKG_CHECK_MODULES([ZIP], [libzip])
AC_SUBST([XML_CFLAGS])
AC_SUBST([XML_LIBS])
AC_SUBST([ZIP_CFLAGS])
AC_SUBST([ZIP_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_OUTPUT
