bin_PROGRAMS         = cogito

cogito_SOURCES       = cogito.l parser.y buffer.c json.c linked_list.c main.c response.c statement.c
cogito_CFLAGS        = $(AM_CFLAGS)

BUILT_SOURCES        = parser.h
AM_CFLAGS            = -fPIC
AM_YFLAGS            = -d

lib_LTLIBRARIES      = libcogito.la
libcogito_la_SOURCES = cogito.l parser.y buffer.c json.c linked_list.c response.c statement.c
include_HEADERS      = cogito.h
pkginclude_HEADERS   = buffer.h json.h linked_list.h response.h statement.h parser.h
