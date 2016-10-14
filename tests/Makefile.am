AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBVSMBR_DLL_IMPORT@

TESTS = \
	test_api_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vsmbr_test_error \
	vsmbr_test_support

vsmbr_test_error_SOURCES = \
	vsmbr_test_error.c \
	vsmbr_test_libcstring.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_unused.h

vsmbr_test_error_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCSTRING_LIBADD@

vsmbr_test_support_SOURCES = \
	vsmbr_test_libcstring.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_support.c \
	vsmbr_test_unused.h

vsmbr_test_support_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

