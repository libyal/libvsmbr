include_HEADERS = \
	libvsmbr.h

pkginclude_HEADERS = \
	libvsmbr/codepage.h \
	libvsmbr/definitions.h \
	libvsmbr/error.h \
	libvsmbr/extern.h \
	libvsmbr/features.h \
	libvsmbr/types.h

EXTRA_DIST = \
	libvsmbr.h.in \
	libvsmbr/definitions.h.in \
	libvsmbr/features.h.in \
	libvsmbr/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libvsmbr.h
	-rm -f libvsmbr/definitions.h
	-rm -f libvsmbr/features.h
	-rm -f libvsmbr/types.h
	-rm -f Makefile

