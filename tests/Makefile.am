TESTS                     = check_buffer check_linked_list check_statement check_response
check_PROGRAMS            = check_buffer check_linked_list check_statement check_response

check_buffer_SOURCES = check_buffer.c $(top_builddir)/src/buffer.h
check_buffer_CFLAGS  = @CHECK_CFLAGS@
check_buffer_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@

check_linked_list_SOURCES = check_linked_list.c $(top_builddir)/src/linked_list.h
check_linked_list_CFLAGS  = @CHECK_CFLAGS@
check_linked_list_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@

check_statement_SOURCES = check_statement.c $(top_builddir)/src/statement.h
check_statement_CFLAGS  = @CHECK_CFLAGS@
check_statement_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@

check_response_SOURCES = check_response.c $(top_builddir)/src/response.h
check_response_CFLAGS  = @CHECK_CFLAGS@
check_response_LDADD   = $(top_builddir)/src/libcogito.la @CHECK_LIBS@
