AC_INIT([cogito], [1.0], [oss@localytics.com])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_PROG_AR
AC_PROG_CC
AM_PROG_CC_C_O
AM_PATH_CHECK([0.9.0],[],[AC_MSG_ERROR([check is missing])])

AC_PROG_YACC
AC_PROG_LEX

LT_INIT

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
