if HAVE_PYTHON
AM_CFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSMBR_DLL_IMPORT@

pyexec_LTLIBRARIES = pyvsmbr.la

pyvsmbr_la_SOURCES = \
	pyvsmbr.c pyvsmbr.h \
	pyvsmbr_error.c pyvsmbr_error.h \
	pyvsmbr_file_object_io_handle.c pyvsmbr_file_object_io_handle.h \
	pyvsmbr_integer.c pyvsmbr_integer.h \
	pyvsmbr_libbfio.h \
	pyvsmbr_libcerror.h \
	pyvsmbr_libclocale.h \
	pyvsmbr_libvsmbr.h \
	pyvsmbr_partition.c pyvsmbr_partition.h \
	pyvsmbr_partitions.c pyvsmbr_partitions.h \
	pyvsmbr_python.h \
	pyvsmbr_unused.h \
	pyvsmbr_volume.c pyvsmbr_volume.h

pyvsmbr_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyvsmbr_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyvsmbr_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

DISTCLEANFILES = \
	Makefile \
	Makefile.in

