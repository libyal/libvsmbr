#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libvsmbr/.libs/libvsmbr.1.dylib && test -f ./pyvsmbr/.libs/pyvsmbr.so;
then
	install_name_tool -change /usr/local/lib/libvsmbr.1.dylib ${PWD}/libvsmbr/.libs/libvsmbr.1.dylib ./pyvsmbr/.libs/pyvsmbr.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

