/*
 * Library partition type test program
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsmbr_test_functions.h"
#include "vsmbr_test_libbfio.h"
#include "vsmbr_test_libcerror.h"
#include "vsmbr_test_libvsmbr.h"
#include "vsmbr_test_macros.h"
#include "vsmbr_test_memory.h"
#include "vsmbr_test_rwlock.h"
#include "vsmbr_test_unused.h"

#include "../libvsmbr/libvsmbr_partition.h"
#include "../libvsmbr/libvsmbr_partition_values.h"

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )

/* Tests the libvsmbr_partition_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	int result                                    = 0;

#if defined( HAVE_VSMBR_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 2;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_partition_initialize(
	          NULL,
	          NULL,
	          partition_values,
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

	partition = (libvsmbr_partition_t *) 0x12345678UL;

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
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

	partition = NULL;

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
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

/* TODO test libvsmbr_partition_values_get_size failing */

#if defined( HAVE_VSMBR_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 * 2 fail in libcthreads_read_write_lock_initialize
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsmbr_partition_initialize with malloc failing
		 */
		vsmbr_test_malloc_attempts_before_fail = test_number;

		result = libvsmbr_partition_initialize(
		          &partition,
		          NULL,
		          partition_values,
		          &error );

		if( vsmbr_test_malloc_attempts_before_fail != -1 )
		{
			vsmbr_test_malloc_attempts_before_fail = -1;

			if( partition != NULL )
			{
				libvsmbr_partition_free(
				 &partition,
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
			 "partition",
			 partition );

			VSMBR_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvsmbr_partition_initialize with memset failing
		 */
		vsmbr_test_memset_attempts_before_fail = test_number;

		result = libvsmbr_partition_initialize(
		          &partition,
		          NULL,
		          partition_values,
		          &error );

		if( vsmbr_test_memset_attempts_before_fail != -1 )
		{
			vsmbr_test_memset_attempts_before_fail = -1;

			if( partition != NULL )
			{
				libvsmbr_partition_free(
				 &partition,
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
			 "partition",
			 partition );

			VSMBR_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSMBR_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_free function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_free(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	int result                                    = 0;

	/* Test error cases
	 */
	result = libvsmbr_partition_free(
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

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libvsmbr_partition_free with pthread_rwlock_destroy failing in libcthreads_read_write_lock_free
	 */
	vsmbr_test_pthread_rwlock_destroy_attempts_before_fail = 0;

	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	if( vsmbr_test_pthread_rwlock_destroy_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_destroy_attempts_before_fail = -1;

		/* Clean up
		 */
		result = libvsmbr_partition_free(
		          &partition,
		          &error );

		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "partition",
		 partition );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NULL(
		 "partition",
		 partition );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_get_type function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_get_type(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	int result                                    = 0;
	uint8_t partition_type                        = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsmbr_partition_get_type(
	          partition,
	          &partition_type,
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
	result = libvsmbr_partition_get_type(
	          NULL,
	          &partition_type,
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

	result = libvsmbr_partition_get_type(
	          partition,
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

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Test libvsmbr_partition_get_type with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsmbr_partition_get_type(
	          partition,
	          &partition_type,
	          &error );

	if( vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsmbr_partition_get_type with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 * WARNING: after this test the lock is still active
	 */
	vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsmbr_partition_get_type(
	          partition,
	          &partition_type,
	          &error );

	if( vsmbr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_internal_partition_read_buffer_from_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_internal_partition_read_buffer_from_file_io_handle(
     void )
{
	uint8_t buffer[ 2048 ];
	uint8_t test_data[ 2048 ];

	libbfio_handle_t *file_io_handle              = NULL;
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	ssize_t read_count                            = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	partition_values->size = 2048;

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = vsmbr_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          2048,
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

	/* Test regular cases
	 */
	read_count = libvsmbr_internal_partition_read_buffer_from_file_io_handle(
	              (libvsmbr_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsmbr_internal_partition_read_buffer_from_file_io_handle(
	              (libvsmbr_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              2048,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsmbr_internal_partition_read_buffer_from_file_io_handle(
	              NULL,
	              file_io_handle,
	              buffer,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsmbr_internal_partition_read_buffer_from_file_io_handle(
	              (libvsmbr_internal_partition_t *) partition,
	              file_io_handle,
	              NULL,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsmbr_internal_partition_read_buffer_from_file_io_handle(
	              (libvsmbr_internal_partition_t *) partition,
	              file_io_handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up file IO handle
	 */
	result = vsmbr_test_close_file_io_handle(
	          &file_io_handle,
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
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_read_buffer(
     void )
{
	uint8_t buffer[ 2048 ];
	uint8_t test_data[ 2048 ];

	libbfio_handle_t *file_io_handle              = NULL;

	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	ssize_t read_count                            = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	partition_values->size = 2048;

	result = vsmbr_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          2048,
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

	result = libvsmbr_partition_initialize(
	          &partition,
	          file_io_handle,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libvsmbr_partition_read_buffer(
	              partition,
	              buffer,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsmbr_partition_read_buffer(
	              partition,
	              buffer,
	              2048,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsmbr_partition_read_buffer(
	              NULL,
	              buffer,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsmbr_partition_read_buffer with libvsmbr_internal_partition_read_buffer_from_file_io_handle failing
	 */
	read_count = libvsmbr_partition_read_buffer(
	              partition,
	              NULL,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Test libvsmbr_partition_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libvsmbr_partition_read_buffer(
	              partition,
	              buffer,
	              512,
	              &error );

	if( vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsmbr_partition_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 * WARNING: after this test the lock is still active
	 */
	vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libvsmbr_partition_read_buffer(
	              partition,
	              buffer,
	              512,
	              &error );

	if( vsmbr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = vsmbr_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_read_buffer_at_offset(
     void )
{
	uint8_t buffer[ 2048 ];
	uint8_t test_data[ 2048 ];

	libbfio_handle_t *file_io_handle              = NULL;

	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	ssize_t read_count                            = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	partition_values->size = 2048;

	result = vsmbr_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          2048,
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

	result = libvsmbr_partition_initialize(
	          &partition,
	          file_io_handle,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libvsmbr_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              0,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libvsmbr_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              2048,
	              512,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsmbr_partition_read_buffer_at_offset(
	              NULL,
	              buffer,
	              512,
	              0,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsmbr_partition_read_buffer_at_offset with libvsmbr_internal_partition_seek_offset failing
	 */
	read_count = libvsmbr_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              -1,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsmbr_partition_read_buffer_at_offset with libvsmbr_internal_partition_read_buffer_from_file_io_handle failing
	 */
	read_count = libvsmbr_partition_read_buffer_at_offset(
	              partition,
	              NULL,
	              512,
	              0,
	              &error );

	VSMBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Test libvsmbr_partition_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libvsmbr_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              0,
	              &error );

	if( vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsmbr_partition_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 * WARNING: after this test the lock is still active
	 */
	vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libvsmbr_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              512,
	              0,
	              &error );

	if( vsmbr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = vsmbr_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_internal_partition_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_internal_partition_seek_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	off64_t offset                                = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	partition_values->size = 2048;

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	offset = libvsmbr_internal_partition_seek_offset(
	          (libvsmbr_internal_partition_t *) partition,
	          512,
	          SEEK_CUR,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 512 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsmbr_internal_partition_seek_offset(
	          (libvsmbr_internal_partition_t *) partition,
	          512,
	          SEEK_CUR,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 1024 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsmbr_internal_partition_seek_offset(
	          (libvsmbr_internal_partition_t *) partition,
	          0,
	          SEEK_END,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 2048 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsmbr_internal_partition_seek_offset(
	          (libvsmbr_internal_partition_t *) partition,
	          0,
	          SEEK_SET,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 0 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvsmbr_internal_partition_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsmbr_internal_partition_seek_offset(
	          (libvsmbr_internal_partition_t *) partition,
	          -1,
	          SEEK_SET,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsmbr_internal_partition_seek_offset(
	          (libvsmbr_internal_partition_t *) partition,
	          0,
	          -1,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_seek_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	off64_t offset                                = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	offset = libvsmbr_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 0 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvsmbr_partition_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libvsmbr_partition_seek_offset with libvsmbr_internal_partition_seek_offset failing
	 */
	offset = libvsmbr_partition_seek_offset(
	          partition,
	          -1,
	          SEEK_SET,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Test libvsmbr_partition_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libvsmbr_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	if( vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsmbr_partition_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 * WARNING: after this test the lock is still active
	 */
	vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	offset = libvsmbr_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	if( vsmbr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_get_offset(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	off64_t offset                                = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsmbr_partition_get_offset(
	          partition,
	          &offset,
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
	result = libvsmbr_partition_get_offset(
	          NULL,
	          &offset,
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

	result = libvsmbr_partition_get_offset(
	          partition,
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

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Test libvsmbr_partition_get_offset with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsmbr_partition_get_offset(
	          partition,
	          &offset,
	          &error );

	if( vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsmbr_partition_get_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 * WARNING: after this test the lock is still active
	 */
	vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsmbr_partition_get_offset(
	          partition,
	          &offset,
	          &error );

	if( vsmbr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_partition_get_size function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_partition_get_size(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvsmbr_partition_t *partition               = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	size64_t size                                 = 0;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libvsmbr_partition_values_initialize(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_values",
	 partition_values );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_initialize(
	          &partition,
	          NULL,
	          partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsmbr_partition_get_size(
	          partition,
	          &size,
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
	result = libvsmbr_partition_get_size(
	          NULL,
	          &size,
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

	result = libvsmbr_partition_get_size(
	          partition,
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

#if defined( HAVE_VSMBR_TEST_RWLOCK )

	/* Test libvsmbr_partition_get_size with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsmbr_partition_get_size(
	          partition,
	          &size,
	          &error );

	if( vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsmbr_partition_get_size with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 * WARNING: after this test the lock is still active
	 */
	vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsmbr_partition_get_size(
	          partition,
	          &size,
	          &error );

	if( vsmbr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsmbr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSMBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSMBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSMBR_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libvsmbr_partition_free(
	          &partition,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_partition_values_free(
	          &partition_values,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_values",
	 partition_values );

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
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
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
	 "libvsmbr_partition_initialize",
	 vsmbr_test_partition_initialize );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_free",
	 vsmbr_test_partition_free );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_get_type",
	 vsmbr_test_partition_get_type );

	VSMBR_TEST_RUN(
	 "libvsmbr_internal_partition_read_buffer_from_file_io_handle",
	 vsmbr_test_internal_partition_read_buffer_from_file_io_handle );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_read_buffer",
	 vsmbr_test_partition_read_buffer );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_read_buffer_at_offset",
	 vsmbr_test_partition_read_buffer_at_offset );

	VSMBR_TEST_RUN(
	 "libvsmbr_internal_partition_seek_offset",
	 vsmbr_test_internal_partition_seek_offset );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_seek_offset",
	 vsmbr_test_partition_seek_offset );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_get_offset",
	 vsmbr_test_partition_get_offset );

	VSMBR_TEST_RUN(
	 "libvsmbr_partition_get_size",
	 vsmbr_test_partition_get_size );

#endif /* defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

