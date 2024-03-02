/*
 * Library volume type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsmbr_test_functions.h"
#include "vsmbr_test_getopt.h"
#include "vsmbr_test_libbfio.h"
#include "vsmbr_test_libcerror.h"
#include "vsmbr_test_libvsmbr.h"
#include "vsmbr_test_macros.h"
#include "vsmbr_test_memory.h"
#include "vsmbr_test_unused.h"

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )
#include "../libvsmbr/libvsmbr_volume.h"
#endif

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vsmbr_test_volume generate verbose output
#define VSMBR_TEST_VOLUME_VERBOSE
 */

#if !defined( LIBVSMBR_HAVE_BFIO )

LIBVSMBR_EXTERN \
int libvsmbr_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_open_file_io_handle(
     libvsmbr_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsmbr_error_t **error );

#endif /* !defined( LIBVSMBR_HAVE_BFIO ) */

/* Creates and opens a source volume
 * Returns 1 if successful or -1 on error
 */
int vsmbr_test_volume_open_source(
     libvsmbr_volume_t **volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "vsmbr_test_volume_open_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libvsmbr_volume_initialize(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	result = libvsmbr_volume_open_file_io_handle(
	          *volume,
	          file_io_handle,
	          LIBVSMBR_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *volume != NULL )
	{
		libvsmbr_volume_free(
		 volume,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source volume
 * Returns 1 if successful or -1 on error
 */
int vsmbr_test_volume_close_source(
     libvsmbr_volume_t **volume,
     libcerror_error_t **error )
{
	static char *function = "vsmbr_test_volume_close_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( libvsmbr_volume_close(
	     *volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close volume.",
		 function );

		result = -1;
	}
	if( libvsmbr_volume_free(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free volume.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libvsmbr_volume_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvsmbr_volume_t *volume       = NULL;
	int result                      = 0;

#if defined( HAVE_VSMBR_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvsmbr_volume_initialize(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_volume_free(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_initialize(
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

	volume = (libvsmbr_volume_t *) 0x12345678UL;

	result = libvsmbr_volume_initialize(
	          &volume,
	          &error );

	volume = NULL;

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
		/* Test libvsmbr_volume_initialize with malloc failing
		 */
		vsmbr_test_malloc_attempts_before_fail = test_number;

		result = libvsmbr_volume_initialize(
		          &volume,
		          &error );

		if( vsmbr_test_malloc_attempts_before_fail != -1 )
		{
			vsmbr_test_malloc_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvsmbr_volume_free(
				 &volume,
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
			 "volume",
			 volume );

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
		/* Test libvsmbr_volume_initialize with memset failing
		 */
		vsmbr_test_memset_attempts_before_fail = test_number;

		result = libvsmbr_volume_initialize(
		          &volume,
		          &error );

		if( vsmbr_test_memset_attempts_before_fail != -1 )
		{
			vsmbr_test_memset_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvsmbr_volume_free(
				 &volume,
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
			 "volume",
			 volume );

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
	if( volume != NULL )
	{
		libvsmbr_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_volume_free function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsmbr_volume_free(
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

/* Tests the libvsmbr_volume_open function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvsmbr_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = vsmbr_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_volume_initialize(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvsmbr_volume_open(
	          volume,
	          narrow_source,
	          LIBVSMBR_OPEN_READ,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_open(
	          NULL,
	          narrow_source,
	          LIBVSMBR_OPEN_READ,
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

	result = libvsmbr_volume_open(
	          volume,
	          NULL,
	          LIBVSMBR_OPEN_READ,
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

	result = libvsmbr_volume_open(
	          volume,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libvsmbr_volume_open(
	          volume,
	          narrow_source,
	          LIBVSMBR_OPEN_READ,
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

	/* Clean up
	 */
	result = libvsmbr_volume_free(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsmbr_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvsmbr_volume_open_wide function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvsmbr_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = vsmbr_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_volume_initialize(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvsmbr_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSMBR_OPEN_READ,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_open_wide(
	          NULL,
	          wide_source,
	          LIBVSMBR_OPEN_READ,
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

	result = libvsmbr_volume_open_wide(
	          volume,
	          NULL,
	          LIBVSMBR_OPEN_READ,
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

	result = libvsmbr_volume_open_wide(
	          volume,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libvsmbr_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSMBR_OPEN_READ,
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

	/* Clean up
	 */
	result = libvsmbr_volume_free(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsmbr_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvsmbr_volume_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsmbr_volume_t *volume        = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSMBR_TEST_ASSERT_IS_NOT_NULL(
         "file_io_handle",
         file_io_handle );

        VSMBR_TEST_ASSERT_IS_NULL(
         "error",
         error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSMBR_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libvsmbr_volume_initialize(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvsmbr_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSMBR_OPEN_READ,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBVSMBR_OPEN_READ,
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

	result = libvsmbr_volume_open_file_io_handle(
	          volume,
	          NULL,
	          LIBVSMBR_OPEN_READ,
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

	result = libvsmbr_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libvsmbr_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSMBR_OPEN_READ,
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

	/* Clean up
	 */
	result = libvsmbr_volume_free(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

        VSMBR_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsmbr_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_volume_close function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsmbr_volume_close(
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

/* Tests the libvsmbr_volume_open and libvsmbr_volume_close functions
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error  = NULL;
	libvsmbr_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libvsmbr_volume_initialize(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvsmbr_volume_open_wide(
	          volume,
	          source,
	          LIBVSMBR_OPEN_READ,
	          &error );
#else
	result = libvsmbr_volume_open(
	          volume,
	          source,
	          LIBVSMBR_OPEN_READ,
	          &error );
#endif

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_volume_close(
	          volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvsmbr_volume_open_wide(
	          volume,
	          source,
	          LIBVSMBR_OPEN_READ,
	          &error );
#else
	result = libvsmbr_volume_open(
	          volume,
	          source,
	          LIBVSMBR_OPEN_READ,
	          &error );
#endif

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_volume_close(
	          volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvsmbr_volume_free(
	          &volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsmbr_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_volume_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_signal_abort(
     libvsmbr_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsmbr_volume_signal_abort(
	          volume,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_signal_abort(
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

/* Tests the libvsmbr_volume_get_bytes_per_sector function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_get_bytes_per_sector(
     libvsmbr_volume_t *volume )
{
	libcerror_error_t *error  = NULL;
	uint32_t bytes_per_sector = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libvsmbr_volume_get_bytes_per_sector(
	          volume,
	          &bytes_per_sector,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_get_bytes_per_sector(
	          NULL,
	          &bytes_per_sector,
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

	result = libvsmbr_volume_get_bytes_per_sector(
	          volume,
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

/* Tests the libvsmbr_volume_get_number_of_partitions function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_get_number_of_partitions(
     libvsmbr_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int number_of_partitions = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsmbr_volume_get_number_of_partitions(
	          volume,
	          &number_of_partitions,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_get_number_of_partitions(
	          NULL,
	          &number_of_partitions,
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

	result = libvsmbr_volume_get_number_of_partitions(
	          volume,
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

/* Tests the libvsmbr_volume_get_partition_by_index function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_volume_get_partition_by_index(
     libvsmbr_volume_t *volume )
{
	libcerror_error_t *error                 = NULL;
	libvsmbr_partition_t *partition_by_index = 0;
	int number_of_partitions                 = 0;
	int result                               = 0;

	/* Test regular cases
	 */
	result = libvsmbr_volume_get_number_of_partitions(
	          volume,
	          &number_of_partitions,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( number_of_partitions == 0 )
	{
		return( 1 );
	}
	result = libvsmbr_volume_get_partition_by_index(
	          volume,
	          0,
	          &partition_by_index,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_by_index",
	 partition_by_index );

	result = libvsmbr_partition_free(
	          &partition_by_index,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_volume_get_partition_by_index(
	          NULL,
	          0,
	          &partition_by_index,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_by_index",
	 partition_by_index );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsmbr_volume_get_partition_by_index(
	          volume,
	          -1,
	          &partition_by_index,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_by_index",
	 partition_by_index );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsmbr_volume_get_partition_by_index(
	          volume,
	          0,
	          NULL,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_by_index",
	 partition_by_index );

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

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsmbr_volume_t *volume        = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = vsmbr_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSMBR_TEST_VOLUME_VERBOSE )
	libvsmbr_notify_set_verbose(
	 1 );
	libvsmbr_notify_set_stream(
	 stderr,
	 NULL );
#endif

	VSMBR_TEST_RUN(
	 "libvsmbr_volume_initialize",
	 vsmbr_test_volume_initialize );

	VSMBR_TEST_RUN(
	 "libvsmbr_volume_free",
	 vsmbr_test_volume_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSMBR_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        VSMBR_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSMBR_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libvsmbr_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		VSMBR_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_open",
		 vsmbr_test_volume_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_open_wide",
		 vsmbr_test_volume_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_open_file_io_handle",
		 vsmbr_test_volume_open_file_io_handle,
		 source );

		VSMBR_TEST_RUN(
		 "libvsmbr_volume_close",
		 vsmbr_test_volume_close );

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_open_close",
		 vsmbr_test_volume_open_close,
		 source );

		/* Initialize volume for tests
		 */
		result = vsmbr_test_volume_open_source(
		          &volume,
		          file_io_handle,
		          &error );

		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "volume",
		 volume );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_signal_abort",
		 vsmbr_test_volume_signal_abort,
		 volume );

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )

		/* TODO: add tests for libvsmbr_volume_open_read */

		/* TODO: add tests for libvsmbr_volume_read_partition_entries */

#endif /* defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT ) */

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_get_bytes_per_sector",
		 vsmbr_test_volume_get_bytes_per_sector,
		 volume );

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_get_number_of_partitions",
		 vsmbr_test_volume_get_number_of_partitions,
		 volume );

		VSMBR_TEST_RUN_WITH_ARGS(
		 "libvsmbr_volume_get_partition_by_index",
		 vsmbr_test_volume_get_partition_by_index,
		 volume );

		/* Clean up
		 */
		result = vsmbr_test_volume_close_source(
		          &volume,
		          &error );

		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "volume",
		 volume );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSMBR_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        VSMBR_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsmbr_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

