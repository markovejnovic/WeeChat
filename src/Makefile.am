## Process this file with automake to generate Makefile.in
AM_CXXFLAGS = $(WeeChat_CFLAGS) $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_LDFLAGS)

bin_PROGRAMS = WeeChat
WeeChat_SOURCES = WeeChat.cc Configuration.cc ConsolePrinter.cc

WeeChat_CPPFLAGS = $(WeeChat_CFLAGS)
WeeChat_LDADD = $(WeeChat_LIBS) $(BOOST_SYSTEM_LIB) $(BOOST_FILESYSTEM_LIB)

CLEANFILES = *~