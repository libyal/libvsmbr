# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSMBR_DLL_IMPORT@

am_pyvsmbr_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
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

pyexec_LTLIBRARIES = pyvsmbr.la

nodist_pyvsmbr_la_SOURCES = $(BUILT_SOURCES)

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

pyvsmbr_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyvsmbr_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvsmbr/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	-rm -f pyvsmbr*.[ch]

distclean: clean
	-rm -f Makefile

