AC_INIT([cogito], [0.0.1], [oss@localytics.com])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_PROG_AR

AC_PROG_CC
AM_PROG_CC_C_O
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_PROG_YACC
AC_PROG_LEX

LT_INIT

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
