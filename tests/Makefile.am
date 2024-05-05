AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSMBR_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSMBR = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_vsmbrinfo.sh \
	$(TESTS_PYVSMBR)

check_SCRIPTS = \
	pyvsmbr_test_partition.py \
	pyvsmbr_test_support.py \
	pyvsmbr_test_volume.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh \
	test_vsmbrinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vsmbr_test_boot_record \
	vsmbr_test_chs_address \
	vsmbr_test_error \
	vsmbr_test_io_handle \
	vsmbr_test_notify \
	vsmbr_test_partition \
	vsmbr_test_partition_entry \
	vsmbr_test_partition_type \
	vsmbr_test_partition_values \
	vsmbr_test_section_values \
	vsmbr_test_sector_data \
	vsmbr_test_support \
	vsmbr_test_tools_info_handle \
	vsmbr_test_tools_output \
	vsmbr_test_tools_signal \
	vsmbr_test_volume

vsmbr_test_boot_record_SOURCES = \
	vsmbr_test_boot_record.c \
	vsmbr_test_functions.c vsmbr_test_functions.h \
	vsmbr_test_libbfio.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_unused.h

vsmbr_test_boot_record_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

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
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_notify.c \
	vsmbr_test_unused.h

vsmbr_test_notify_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_partition_SOURCES = \
	vsmbr_test_functions.c vsmbr_test_functions.h \
	vsmbr_test_getopt.c vsmbr_test_getopt.h \
	vsmbr_test_libbfio.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_partition.c \
	vsmbr_test_rwlock.c vsmbr_test_rwlock.h

vsmbr_test_partition_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

vsmbr_test_partition_entry_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_partition_entry.c \
	vsmbr_test_unused.h

vsmbr_test_partition_entry_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_partition_type_SOURCES = \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_partition_type.c \
	vsmbr_test_unused.h

vsmbr_test_partition_type_LDADD = \
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

vsmbr_test_sector_data_SOURCES = \
	vsmbr_test_functions.c vsmbr_test_functions.h \
	vsmbr_test_libbfio.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_sector_data.c \
	vsmbr_test_unused.h

vsmbr_test_sector_data_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_support_SOURCES = \
	vsmbr_test_functions.c vsmbr_test_functions.h \
	vsmbr_test_getopt.c vsmbr_test_getopt.h \
	vsmbr_test_libbfio.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_libclocale.h \
	vsmbr_test_libcnotify.h \
	vsmbr_test_libuna.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_support.c \
	vsmbr_test_unused.h

vsmbr_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_tools_info_handle_SOURCES = \
	../vsmbrtools/info_handle.c ../vsmbrtools/info_handle.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_tools_info_handle.c \
	vsmbr_test_unused.h

vsmbr_test_tools_info_handle_LDADD = \
	@LIBCLOCALE_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_tools_output_SOURCES = \
	../vsmbrtools/vsmbrtools_output.c ../vsmbrtools/vsmbrtools_output.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_macros.h \
	vsmbr_test_tools_output.c \
	vsmbr_test_unused.h

vsmbr_test_tools_output_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_tools_signal_SOURCES = \
	../vsmbrtools/vsmbrtools_signal.c ../vsmbrtools/vsmbrtools_signal.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_macros.h \
	vsmbr_test_tools_signal.c \
	vsmbr_test_unused.h

vsmbr_test_tools_signal_LDADD = \
	../libvsmbr/libvsmbr.la \
	@LIBCERROR_LIBADD@

vsmbr_test_volume_SOURCES = \
	vsmbr_test_functions.c vsmbr_test_functions.h \
	vsmbr_test_getopt.c vsmbr_test_getopt.h \
	vsmbr_test_libbfio.h \
	vsmbr_test_libcerror.h \
	vsmbr_test_libclocale.h \
	vsmbr_test_libcnotify.h \
	vsmbr_test_libuna.h \
	vsmbr_test_libvsmbr.h \
	vsmbr_test_macros.h \
	vsmbr_test_memory.c vsmbr_test_memory.h \
	vsmbr_test_rwlock.c vsmbr_test_rwlock.h \
	vsmbr_test_unused.h \
	vsmbr_test_volume.c

vsmbr_test_volume_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

DISTCLEANFILES = \
	Makefile \
	Makefile.in \
	notify_stream.log

