bin_PROGRAMS = cogito
cogito_SOURCES = cogito.l parser.y json.c linked-list.c main.c statement.c

BUILT_SOURCES = parser.h
AM_YFLAGS = -d

lib_LIBRARIES = libcogito.a
libcogito_a_SOURCES = cogito.l parser.y json.c linked-list.c statement.c
include_HEADERS = cogito.h
pkginclude_HEADERS = json.h linked-list.h statement.h parser.h
