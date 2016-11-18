bin_PROGRAMS         = cogito

cogito_SOURCES       = cogito.l parser.y buffer.c json.c linked_list.c main.c statement.c
cogito_CFLAGS        = $(AM_CFLAGS)

BUILT_SOURCES        = parser.h
AM_CFLAGS            = -fPIC
AM_YFLAGS            = -d

lib_LTLIBRARIES      = libcogito.la
libcogito_la_SOURCES = cogito.l parser.y buffer.c json.c linked_list.c statement.c
include_HEADERS      = cogito.h
pkginclude_HEADERS   = buffer.h errors.h json.h linked_list.h statement.h parser.h
