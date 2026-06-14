#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libvsmbr/.libs/libvsmbr.1.dylib && test -f ./pyvsmbr/.libs/pyvsmbr.so
then
	install_name_tool -change /usr/local/lib/libvsmbr.1.dylib ${PWD}/libvsmbr/.libs/libvsmbr.1.dylib ./pyvsmbr/.libs/pyvsmbr.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

