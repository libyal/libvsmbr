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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyvsmbr_test_partition.py \
	pyvsmbr_test_support.py \
	pyvsmbr_test_volume.py

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
	vsmbr_test_extern.h \
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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

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
	vsmbr_test_extern.h \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libvsmbr.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libvsmbr

test_inputs_pyvsmbr.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyvsmbr

test_inputs_vsmbrinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) vsmbrinfo

test_library: \
	package.m4 \
	test_inputs_libvsmbr.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pyvsmbr.at \
	test_macros.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_vsmbrinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

