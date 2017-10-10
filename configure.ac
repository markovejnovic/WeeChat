AC_PREREQ([2.60])

AC_INIT([WeeChat], [0.1], [marko.vejnovic@hotmail.com])
AM_INIT_AUTOMAKE([1.9 -Wall foreign])
AM_SILENT_RULES([no])

AC_PROG_CXX
PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES([WeeChat], [
	gtkmm-3.0
])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT