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
	@LIBVSMBR_DLL_EXPORT@

lib_LTLIBRARIES = libvsmbr.la

libvsmbr_la_SOURCES = \
	libvsmbr.c \
	libvsmbr_boot_record.c libvsmbr_boot_record.h \
	libvsmbr_chs_address.c libvsmbr_chs_address.h \
	libvsmbr_debug.c libvsmbr_debug.h \
	libvsmbr_definitions.h \
	libvsmbr_error.c libvsmbr_error.h \
	libvsmbr_extern.h \
	libvsmbr_io_handle.c libvsmbr_io_handle.h \
	libvsmbr_libbfio.h \
	libvsmbr_libcdata.h \
	libvsmbr_libcerror.h \
	libvsmbr_libclocale.h \
	libvsmbr_libcnotify.h \
	libvsmbr_libcthreads.h \
	libvsmbr_libfcache.h \
	libvsmbr_libfdata.h \
	libvsmbr_notify.c libvsmbr_notify.h \
	libvsmbr_partition.c libvsmbr_partition.h \
	libvsmbr_partition_entry.c libvsmbr_partition_entry.h \
	libvsmbr_partition_type.c libvsmbr_partition_type.h \
	libvsmbr_partition_values.c libvsmbr_partition_values.h \
	libvsmbr_section_values.c libvsmbr_section_values.h \
	libvsmbr_sector_data.c libvsmbr_sector_data.h \
	libvsmbr_support.c libvsmbr_support.h \
	libvsmbr_types.h \
	libvsmbr_unused.h \
	libvsmbr_volume.c libvsmbr_volume.h \
	vsmbr_boot_record.h \
	vsmbr_partition_entry.h

libvsmbr_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@PTHREAD_LIBADD@

libvsmbr_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libvsmbr_definitions.h.in \
	libvsmbr.rc \
	libvsmbr.rc.in

DISTCLEANFILES = \
	libvsmbr_definitions.h \
	libvsmbr.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libvsmbr ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvsmbr_la_SOURCES)

