/*
 * Library section_values type test program
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsmbr_test_libcerror.h"
#include "vsmbr_test_libvsmbr.h"
#include "vsmbr_test_macros.h"
#include "vsmbr_test_memory.h"
#include "vsmbr_test_unused.h"

#include "../libvsmbr/libvsmbr_section_values.h"

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )

/* Tests the libvsmbr_section_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_section_values_initialize(
     void )
{
	libcerror_error_t *error                  = NULL;
	libvsmbr_section_values_t *section_values = NULL;
	int result                                = 0;

#if defined( HAVE_VSMBR_TEST_MEMORY )
	int number_of_malloc_fail_tests           = 1;
	int number_of_memset_fail_tests           = 1;
	int test_number                           = 0;
#endif

	/* Test regular cases
	 */
	result = libvsmbr_section_values_initialize(
	          &section_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "section_values",
	 section_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_section_values_free(
	          &section_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "section_values",
	 section_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_section_values_initialize(
	          NULL,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	section_values = (libvsmbr_section_values_t *) 0x12345678UL;

	result = libvsmbr_section_values_initialize(
	          &section_values,
	          &error );

	section_values = NULL;

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSMBR_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsmbr_section_values_initialize with malloc failing
		 */
		vsmbr_test_malloc_attempts_before_fail = test_number;

		result = libvsmbr_section_values_initialize(
		          &section_values,
		          &error );

		if( vsmbr_test_malloc_attempts_before_fail != -1 )
		{
			vsmbr_test_malloc_attempts_before_fail = -1;

			if( section_values != NULL )
			{
				libvsmbr_section_values_free(
				 &section_values,
				 NULL );
			}
		}
		else
		{
			VSMBR_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSMBR_TEST_ASSERT_IS_NULL(
			 "section_values",
			 section_values );

			VSMBR_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvsmbr_section_values_initialize with memset failing
		 */
		vsmbr_test_memset_attempts_before_fail = test_number;

		result = libvsmbr_section_values_initialize(
		          &section_values,
		          &error );

		if( vsmbr_test_memset_attempts_before_fail != -1 )
		{
			vsmbr_test_memset_attempts_before_fail = -1;

			if( section_values != NULL )
			{
				libvsmbr_section_values_free(
				 &section_values,
				 NULL );
			}
		}
		else
		{
			VSMBR_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSMBR_TEST_ASSERT_IS_NULL(
			 "section_values",
			 section_values );

			VSMBR_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSMBR_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( section_values != NULL )
	{
		libvsmbr_section_values_free(
		 &section_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_section_values_free function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_section_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsmbr_section_values_free(
	          NULL,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc VSMBR_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] VSMBR_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc VSMBR_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] VSMBR_TEST_ATTRIBUTE_UNUSED )
#endif
{
	VSMBR_TEST_UNREFERENCED_PARAMETER( argc )
	VSMBR_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )

	VSMBR_TEST_RUN(
	 "libvsmbr_section_values_initialize",
	 vsmbr_test_section_values_initialize );

	VSMBR_TEST_RUN(
	 "libvsmbr_section_values_free",
	 vsmbr_test_section_values_free );

#endif /* defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

