#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([Broke], [0.1], [reidmv@pdx.edu])
AC_CONFIG_SRCDIR([src/broke.c])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([GTK], [gtk+-2.0 >= 1.3.13])
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
PKG_CHECK_MODULES([LIBGDA], [libgda-4.0])
AC_SUBST(LIBGDA_CFLAGS)
AC_SUBST(LIBGDA_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
