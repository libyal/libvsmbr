AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vsmbrinfo

vsmbrinfo_SOURCES = \
	info_handle.c info_handle.h \
	vsmbrtools_getopt.c vsmbrtools_getopt.h \
	vsmbrtools_i18n.h \
	vsmbrinfo.c \
	vsmbrtools_libbfio.h \
	vsmbrtools_libcerror.h \
	vsmbrtools_libclocale.h \
	vsmbrtools_libcnotify.h \
	vsmbrtools_libuna.h \
	vsmbrtools_libvsmbr.h \
	vsmbrtools_output.c vsmbrtools_output.h \
	vsmbrtools_signal.c vsmbrtools_signal.h \
	vsmbrtools_unused.h

vsmbrinfo_LDADD = \
	@LIBUNA_LIBADD@ \
	../libvsmbr/libvsmbr.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on vsmbrinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vsmbrinfo_SOURCES)

