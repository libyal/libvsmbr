AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSMBR_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSMBR =
endif

TESTS = \
	test_library.sh \
	$(TESTS_PYVSMBR)

check_SCRIPTS = \
	pyvsmbr_test_support.py \
	test_library.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vsmbr_test_chs_address \
	vsmbr_test_error \
	vsmbr_test_handle \
	vsmbr_test_io_handle \
	vsmbr_test_notify \
	vsmbr_test_partition \
	vsmbr_test_partition_values \
	vsmbr_test_section_values \
	vsmbr_test_support \
	vsmbr_test_volume_type

vsmbr_test_chs_address_SOURCES = \
	vsmbr_test_chs_address.c \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_unused.h

vsmbr_test_chs_address_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_error_SOURCES = \
	vsmbr_test_error.c \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_unused.h

vsmbr_test_error_LDADD = \
	../libvsmbr/libvsmbr.la

vsmbr_test_handle_SOURCES = \
	vsmbr_test_getopt.c vsmbr_test_getopt.h \
	vsmbr_test_handle.c \
	vsmbr_test_libcerror.h \
	vsmbr_test_libclocale.h \
	vsmbr_test_libcnotify.h \
	vsmbr_test_libuna.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h

vsmbr_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

vsmbr_test_io_handle_SOURCES = \
	vsmbr_test_io_handle.c \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_unused.h

vsmbr_test_io_handle_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_notify_SOURCES = \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_notify.c \
	vsmbr_test_unused.h

vsmbr_test_notify_LDADD = \
	../libvsmbr/libvsmbr.la

vsmbr_test_partition_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_partition.c \
	vsmbr_test_unused.h

vsmbr_test_partition_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_partition_values_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_partition_values.c \
	vsmbr_test_unused.h

vsmbr_test_partition_values_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_section_values_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_section_values.c \
	vsmbr_test_unused.h

vsmbr_test_section_values_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_support_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_support.c \
	vsmbr_test_unused.h

vsmbr_test_support_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_volume_type_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_unused.h \
	vsmbr_test_volume_type.c

vsmbr_test_volume_type_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

