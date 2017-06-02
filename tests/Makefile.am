TESTS                     = check_buffer check_list check_statement
check_PROGRAMS            = check_buffer check_list check_statement

check_buffer_SOURCES = check_buffer.c $(top_builddir)/src/buffer.h
check_buffer_CFLAGS  = @CHECK_CFLAGS@
check_buffer_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@

check_list_SOURCES = check_list.c $(top_builddir)/src/list.h
check_list_CFLAGS  = @CHECK_CFLAGS@
check_list_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@

check_statement_SOURCES = check_statement.c $(top_builddir)/src/statement.h
check_statement_CFLAGS  = @CHECK_CFLAGS@
check_statement_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@
