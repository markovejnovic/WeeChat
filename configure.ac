AC_PREREQ([2.61])
AC_INIT([WeeChat], [0.1], [marko.vejnovic@hotmail.com])
AC_CONFIG_AUX_DIR([aux-dist])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_MAKE_SET
AC_PROG_CXX
AC_LANG(C++)

PKG_PROG_PKG_CONFIG

AC_CONFIG_MACRO_DIR([m4])

AX_BOOST_BASE([1.53],,[AC_MSG_ERROR([No boost found.])])
AX_BOOST_SYSTEM([mt])
AX_BOOST_FILESYSTEM([mt])

PKG_CHECK_MODULES([WeeChat], [
	gtkmm-3.0
])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT