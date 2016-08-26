bin_PROGRAMS = cogito
cogito_SOURCES = cogito.l parser.y json.c linked-list.c main.c response.c statement.c smart_string.c

BUILT_SOURCES = parser.h
AM_YFLAGS = -d

lib_LIBRARIES = libcogito.a
libcogito_a_SOURCES = cogito.l parser.y json.c linked-list.c response.c statement.c smart_string.c
include_HEADERS = cogito.h
pkginclude_HEADERS = json.h linked-list.h response.h statement.h smart_string.h parser.h
