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
	/bin/rm -f libvsmbr.h
	/bin/rm -f libvsmbr/definitions.h
	/bin/rm -f libvsmbr/features.h
	/bin/rm -f libvsmbr/types.h
	/bin/rm -f Makefile

