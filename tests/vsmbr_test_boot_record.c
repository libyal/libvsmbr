/*
 * Library boot_record type test program
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

#include "vsmbr_test_functions.h"
#include "vsmbr_test_libcerror.h"
#include "vsmbr_test_libvsmbr.h"
#include "vsmbr_test_macros.h"
#include "vsmbr_test_memory.h"
#include "vsmbr_test_unused.h"

#include "../libvsmbr/libvsmbr_boot_record.h"
#include "../libvsmbr/libvsmbr_partition_entry.h"

uint8_t vsmbr_test_boot_record_data1[ 512 ] = {
	0x33, 0xc0, 0x8e, 0xd0, 0xbc, 0x00, 0x7c, 0x8e, 0xc0, 0x8e, 0xd8, 0xbe, 0x00, 0x7c, 0xbf, 0x00,
	0x06, 0xb9, 0x00, 0x02, 0xfc, 0xf3, 0xa4, 0x50, 0x68, 0x1c, 0x06, 0xcb, 0xfb, 0xb9, 0x04, 0x00,
	0xbd, 0xbe, 0x07, 0x80, 0x7e, 0x00, 0x00, 0x7c, 0x0b, 0x0f, 0x85, 0x0e, 0x01, 0x83, 0xc5, 0x10,
	0xe2, 0xf1, 0xcd, 0x18, 0x88, 0x56, 0x00, 0x55, 0xc6, 0x46, 0x11, 0x05, 0xc6, 0x46, 0x10, 0x00,
	0xb4, 0x41, 0xbb, 0xaa, 0x55, 0xcd, 0x13, 0x5d, 0x72, 0x0f, 0x81, 0xfb, 0x55, 0xaa, 0x75, 0x09,
	0xf7, 0xc1, 0x01, 0x00, 0x74, 0x03, 0xfe, 0x46, 0x10, 0x66, 0x60, 0x80, 0x7e, 0x10, 0x00, 0x74,
	0x26, 0x66, 0x68, 0x00, 0x00, 0x00, 0x00, 0x66, 0xff, 0x76, 0x08, 0x68, 0x00, 0x00, 0x68, 0x00,
	0x7c, 0x68, 0x01, 0x00, 0x68, 0x10, 0x00, 0xb4, 0x42, 0x8a, 0x56, 0x00, 0x8b, 0xf4, 0xcd, 0x13,
	0x9f, 0x83, 0xc4, 0x10, 0x9e, 0xeb, 0x14, 0xb8, 0x01, 0x02, 0xbb, 0x00, 0x7c, 0x8a, 0x56, 0x00,
	0x8a, 0x76, 0x01, 0x8a, 0x4e, 0x02, 0x8a, 0x6e, 0x03, 0xcd, 0x13, 0x66, 0x61, 0x73, 0x1c, 0xfe,
	0x4e, 0x11, 0x75, 0x0c, 0x80, 0x7e, 0x00, 0x80, 0x0f, 0x84, 0x8a, 0x00, 0xb2, 0x80, 0xeb, 0x84,
	0x55, 0x32, 0xe4, 0x8a, 0x56, 0x00, 0xcd, 0x13, 0x5d, 0xeb, 0x9e, 0x81, 0x3e, 0xfe, 0x7d, 0x55,
	0xaa, 0x75, 0x6e, 0xff, 0x76, 0x00, 0xe8, 0x8d, 0x00, 0x75, 0x17, 0xfa, 0xb0, 0xd1, 0xe6, 0x64,
	0xe8, 0x83, 0x00, 0xb0, 0xdf, 0xe6, 0x60, 0xe8, 0x7c, 0x00, 0xb0, 0xff, 0xe6, 0x64, 0xe8, 0x75,
	0x00, 0xfb, 0xb8, 0x00, 0xbb, 0xcd, 0x1a, 0x66, 0x23, 0xc0, 0x75, 0x3b, 0x66, 0x81, 0xfb, 0x54,
	0x43, 0x50, 0x41, 0x75, 0x32, 0x81, 0xf9, 0x02, 0x01, 0x72, 0x2c, 0x66, 0x68, 0x07, 0xbb, 0x00,
	0x00, 0x66, 0x68, 0x00, 0x02, 0x00, 0x00, 0x66, 0x68, 0x08, 0x00, 0x00, 0x00, 0x66, 0x53, 0x66,
	0x53, 0x66, 0x55, 0x66, 0x68, 0x00, 0x00, 0x00, 0x00, 0x66, 0x68, 0x00, 0x7c, 0x00, 0x00, 0x66,
	0x61, 0x68, 0x00, 0x00, 0x07, 0xcd, 0x1a, 0x5a, 0x32, 0xf6, 0xea, 0x00, 0x7c, 0x00, 0x00, 0xcd,
	0x18, 0xa0, 0xb7, 0x07, 0xeb, 0x08, 0xa0, 0xb6, 0x07, 0xeb, 0x03, 0xa0, 0xb5, 0x07, 0x32, 0xe4,
	0x05, 0x00, 0x07, 0x8b, 0xf0, 0xac, 0x3c, 0x00, 0x74, 0x09, 0xbb, 0x07, 0x00, 0xb4, 0x0e, 0xcd,
	0x10, 0xeb, 0xf2, 0xf4, 0xeb, 0xfd, 0x2b, 0xc9, 0xe4, 0x64, 0xeb, 0x00, 0x24, 0x02, 0xe0, 0xf8,
	0x24, 0x02, 0xc3, 0x49, 0x6e, 0x76, 0x61, 0x6c, 0x69, 0x64, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69,
	0x74, 0x69, 0x6f, 0x6e, 0x20, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x00, 0x45, 0x72, 0x72, 0x6f, 0x72,
	0x20, 0x6c, 0x6f, 0x61, 0x64, 0x69, 0x6e, 0x67, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69,
	0x6e, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x00, 0x4d, 0x69, 0x73, 0x73, 0x69, 0x6e,
	0x67, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6e, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74,
	0x65, 0x6d, 0x00, 0x00, 0x00, 0x63, 0x7b, 0x9a, 0x1a, 0x43, 0x5b, 0x69, 0x00, 0x00, 0x80, 0x20,
	0x21, 0x00, 0x07, 0xdf, 0x13, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0xdf,
	0x14, 0x0c, 0x07, 0xfe, 0xff, 0xff, 0x00, 0x28, 0x03, 0x00, 0x00, 0xd0, 0x1c, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xaa };

uint8_t vsmbr_test_boot_record_error_data1[ 512 ] = {
	0x33, 0xc0, 0x8e, 0xd0, 0xbc, 0x00, 0x7c, 0x8e, 0xc0, 0x8e, 0xd8, 0xbe, 0x00, 0x7c, 0xbf, 0x00,
	0x06, 0xb9, 0x00, 0x02, 0xfc, 0xf3, 0xa4, 0x50, 0x68, 0x1c, 0x06, 0xcb, 0xfb, 0xb9, 0x04, 0x00,
	0xbd, 0xbe, 0x07, 0x80, 0x7e, 0x00, 0x00, 0x7c, 0x0b, 0x0f, 0x85, 0x0e, 0x01, 0x83, 0xc5, 0x10,
	0xe2, 0xf1, 0xcd, 0x18, 0x88, 0x56, 0x00, 0x55, 0xc6, 0x46, 0x11, 0x05, 0xc6, 0x46, 0x10, 0x00,
	0xb4, 0x41, 0xbb, 0xaa, 0x55, 0xcd, 0x13, 0x5d, 0x72, 0x0f, 0x81, 0xfb, 0x55, 0xaa, 0x75, 0x09,
	0xf7, 0xc1, 0x01, 0x00, 0x74, 0x03, 0xfe, 0x46, 0x10, 0x66, 0x60, 0x80, 0x7e, 0x10, 0x00, 0x74,
	0x26, 0x66, 0x68, 0x00, 0x00, 0x00, 0x00, 0x66, 0xff, 0x76, 0x08, 0x68, 0x00, 0x00, 0x68, 0x00,
	0x7c, 0x68, 0x01, 0x00, 0x68, 0x10, 0x00, 0xb4, 0x42, 0x8a, 0x56, 0x00, 0x8b, 0xf4, 0xcd, 0x13,
	0x9f, 0x83, 0xc4, 0x10, 0x9e, 0xeb, 0x14, 0xb8, 0x01, 0x02, 0xbb, 0x00, 0x7c, 0x8a, 0x56, 0x00,
	0x8a, 0x76, 0x01, 0x8a, 0x4e, 0x02, 0x8a, 0x6e, 0x03, 0xcd, 0x13, 0x66, 0x61, 0x73, 0x1c, 0xfe,
	0x4e, 0x11, 0x75, 0x0c, 0x80, 0x7e, 0x00, 0x80, 0x0f, 0x84, 0x8a, 0x00, 0xb2, 0x80, 0xeb, 0x84,
	0x55, 0x32, 0xe4, 0x8a, 0x56, 0x00, 0xcd, 0x13, 0x5d, 0xeb, 0x9e, 0x81, 0x3e, 0xfe, 0x7d, 0x55,
	0xaa, 0x75, 0x6e, 0xff, 0x76, 0x00, 0xe8, 0x8d, 0x00, 0x75, 0x17, 0xfa, 0xb0, 0xd1, 0xe6, 0x64,
	0xe8, 0x83, 0x00, 0xb0, 0xdf, 0xe6, 0x60, 0xe8, 0x7c, 0x00, 0xb0, 0xff, 0xe6, 0x64, 0xe8, 0x75,
	0x00, 0xfb, 0xb8, 0x00, 0xbb, 0xcd, 0x1a, 0x66, 0x23, 0xc0, 0x75, 0x3b, 0x66, 0x81, 0xfb, 0x54,
	0x43, 0x50, 0x41, 0x75, 0x32, 0x81, 0xf9, 0x02, 0x01, 0x72, 0x2c, 0x66, 0x68, 0x07, 0xbb, 0x00,
	0x00, 0x66, 0x68, 0x00, 0x02, 0x00, 0x00, 0x66, 0x68, 0x08, 0x00, 0x00, 0x00, 0x66, 0x53, 0x66,
	0x53, 0x66, 0x55, 0x66, 0x68, 0x00, 0x00, 0x00, 0x00, 0x66, 0x68, 0x00, 0x7c, 0x00, 0x00, 0x66,
	0x61, 0x68, 0x00, 0x00, 0x07, 0xcd, 0x1a, 0x5a, 0x32, 0xf6, 0xea, 0x00, 0x7c, 0x00, 0x00, 0xcd,
	0x18, 0xa0, 0xb7, 0x07, 0xeb, 0x08, 0xa0, 0xb6, 0x07, 0xeb, 0x03, 0xa0, 0xb5, 0x07, 0x32, 0xe4,
	0x05, 0x00, 0x07, 0x8b, 0xf0, 0xac, 0x3c, 0x00, 0x74, 0x09, 0xbb, 0x07, 0x00, 0xb4, 0x0e, 0xcd,
	0x10, 0xeb, 0xf2, 0xf4, 0xeb, 0xfd, 0x2b, 0xc9, 0xe4, 0x64, 0xeb, 0x00, 0x24, 0x02, 0xe0, 0xf8,
	0x24, 0x02, 0xc3, 0x49, 0x6e, 0x76, 0x61, 0x6c, 0x69, 0x64, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69,
	0x74, 0x69, 0x6f, 0x6e, 0x20, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x00, 0x45, 0x72, 0x72, 0x6f, 0x72,
	0x20, 0x6c, 0x6f, 0x61, 0x64, 0x69, 0x6e, 0x67, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69,
	0x6e, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x00, 0x4d, 0x69, 0x73, 0x73, 0x69, 0x6e,
	0x67, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6e, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74,
	0x65, 0x6d, 0x00, 0x00, 0x00, 0x63, 0x7b, 0x9a, 0x1a, 0x43, 0x5b, 0x69, 0x00, 0x00, 0x80, 0x20,
	0x21, 0x00, 0x07, 0xdf, 0x13, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0xdf,
	0x14, 0x0c, 0x07, 0xfe, 0xff, 0xff, 0x00, 0x28, 0x03, 0x00, 0x00, 0xd0, 0x1c, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff };

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )

/* Tests the libvsmbr_boot_record_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_boot_record_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libvsmbr_boot_record_t *boot_record = NULL;
	int result                          = 0;

#if defined( HAVE_VSMBR_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 2;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libvsmbr_boot_record_initialize(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "boot_record",
	 boot_record );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_boot_record_free(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "boot_record",
	 boot_record );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsmbr_boot_record_initialize(
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

	boot_record = (libvsmbr_boot_record_t *) 0x12345678UL;

	result = libvsmbr_boot_record_initialize(
	          &boot_record,
	          &error );

	boot_record = NULL;

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
		/* Test libvsmbr_boot_record_initialize with malloc failing
		 */
		vsmbr_test_malloc_attempts_before_fail = test_number;

		result = libvsmbr_boot_record_initialize(
		          &boot_record,
		          &error );

		if( vsmbr_test_malloc_attempts_before_fail != -1 )
		{
			vsmbr_test_malloc_attempts_before_fail = -1;

			if( boot_record != NULL )
			{
				libvsmbr_boot_record_free(
				 &boot_record,
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
			 "boot_record",
			 boot_record );

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
		/* Test libvsmbr_boot_record_initialize with memset failing
		 */
		vsmbr_test_memset_attempts_before_fail = test_number;

		result = libvsmbr_boot_record_initialize(
		          &boot_record,
		          &error );

		if( vsmbr_test_memset_attempts_before_fail != -1 )
		{
			vsmbr_test_memset_attempts_before_fail = -1;

			if( boot_record != NULL )
			{
				libvsmbr_boot_record_free(
				 &boot_record,
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
			 "boot_record",
			 boot_record );

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
	if( boot_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &boot_record,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_boot_record_free function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_boot_record_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsmbr_boot_record_free(
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

/* Tests the libvsmbr_boot_record_read_data function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_boot_record_read_data(
     void )
{
	libcerror_error_t *error            = NULL;
	libvsmbr_boot_record_t *boot_record = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libvsmbr_boot_record_initialize(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "boot_record",
	 boot_record );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          vsmbr_test_boot_record_data1,
	          512,
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
	result = libvsmbr_boot_record_read_data(
	          NULL,
	          vsmbr_test_boot_record_data1,
	          512,
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

	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          NULL,
	          512,
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

	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          vsmbr_test_boot_record_data1,
	          (size_t) SSIZE_MAX + 1,
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

	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          vsmbr_test_boot_record_data1,
	          0,
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

	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          vsmbr_test_boot_record_error_data1,
	          512,
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

#if defined( HAVE_VSMBR_TEST_MEMORY )

	/* Test libvsmbr_boot_record_read_data with malloc failing in libvsmbr_partition_entry_initialize
	 */
	vsmbr_test_malloc_attempts_before_fail = 0;

	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          vsmbr_test_boot_record_data1,
	          512,
	          &error );

	if( vsmbr_test_malloc_attempts_before_fail != -1 )
	{
		vsmbr_test_malloc_attempts_before_fail = -1;
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
#endif /* defined( HAVE_VSMBR_TEST_MEMORY ) */

/* TODO test with libvsmbr_partition_entry_read_data failing */

/* TODO test with libcdata_array_append_entry failing */

	/* Clean up
	 */
	result = libvsmbr_boot_record_free(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "boot_record",
	 boot_record );

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
	if( boot_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &boot_record,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsmbr_boot_record_get_number_of_partition_entries function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_boot_record_get_number_of_partition_entries(
     libvsmbr_boot_record_t *boot_record )
{
	libcerror_error_t *error               = NULL;
	int number_of_partition_entries        = 0;
	int number_of_partition_entries_is_set = 0;
	int result                             = 0;

	/* Test regular cases
	 */
	result = libvsmbr_boot_record_get_number_of_partition_entries(
	          boot_record,
	          &number_of_partition_entries,
	          &error );

	VSMBR_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_partition_entries_is_set = result;

	/* Test error cases
	 */
	result = libvsmbr_boot_record_get_number_of_partition_entries(
	          NULL,
	          &number_of_partition_entries,
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

	if( number_of_partition_entries_is_set != 0 )
	{
		result = libvsmbr_boot_record_get_number_of_partition_entries(
		          boot_record,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsmbr_boot_record_get_partition_entry_by_index function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_boot_record_get_partition_entry_by_index(
     libvsmbr_boot_record_t *boot_record )
{
	libcerror_error_t *error                    = NULL;
	libvsmbr_partition_entry_t *partition_entry = 0;
	int result                                  = 0;

	/* Test regular cases
	 */
	result = libvsmbr_boot_record_get_partition_entry_by_index(
	          boot_record,
	          0,
	          &partition_entry,
	          &error );

	VSMBR_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "partition_entry",
	 partition_entry );

	partition_entry = NULL;

	/* Test error cases
	 */
	result = libvsmbr_boot_record_get_partition_entry_by_index(
	          NULL,
	          0,
	          &partition_entry,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_entry",
	 partition_entry );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsmbr_boot_record_get_partition_entry_by_index(
	          boot_record,
	          -1,
	          &partition_entry,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_entry",
	 partition_entry );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsmbr_boot_record_get_partition_entry_by_index(
	          boot_record,
	          0,
	          NULL,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "partition_entry",
	 partition_entry );

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

/* Tests the libvsmbr_boot_record_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsmbr_test_boot_record_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libvsmbr_boot_record_t *boot_record = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libvsmbr_boot_record_initialize(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "boot_record",
	 boot_record );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = vsmbr_test_open_file_io_handle(
	          &file_io_handle,
	          vsmbr_test_boot_record_data1,
	          512,
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
	result = libvsmbr_boot_record_read_file_io_handle(
	          boot_record,
	          file_io_handle,
	          0,
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
	result = libvsmbr_boot_record_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
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

	result = libvsmbr_boot_record_read_file_io_handle(
	          boot_record,
	          NULL,
	          0,
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

	result = libvsmbr_boot_record_read_file_io_handle(
	          boot_record,
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

	/* Test data too small
	 */
	result = vsmbr_test_open_file_io_handle(
	          &file_io_handle,
	          vsmbr_test_boot_record_data1,
	          8,
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

	result = libvsmbr_boot_record_read_file_io_handle(
	          boot_record,
	          file_io_handle,
	          0,
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

	/* Test data invalid
	 */
	result = vsmbr_test_open_file_io_handle(
	          &file_io_handle,
	          vsmbr_test_boot_record_error_data1,
	          512,
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

	result = libvsmbr_boot_record_read_file_io_handle(
	          boot_record,
	          file_io_handle,
	          0,
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
	result = libvsmbr_boot_record_free(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "boot_record",
	 boot_record );

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
	if( boot_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &boot_record,
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
#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )
	libcerror_error_t *error            = NULL;
	libvsmbr_boot_record_t *boot_record = NULL;
	int result                          = 0;
#endif

	VSMBR_TEST_UNREFERENCED_PARAMETER( argc )
	VSMBR_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )

	VSMBR_TEST_RUN(
	 "libvsmbr_boot_record_initialize",
	 vsmbr_test_boot_record_initialize );

	VSMBR_TEST_RUN(
	 "libvsmbr_boot_record_free",
	 vsmbr_test_boot_record_free );

	VSMBR_TEST_RUN(
	 "libvsmbr_boot_record_read_data",
	 vsmbr_test_boot_record_read_data );

	VSMBR_TEST_RUN(
	 "libvsmbr_boot_record_read_file_io_handle",
	 vsmbr_test_boot_record_read_file_io_handle );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize boot_record for tests
	 */
	result = libvsmbr_boot_record_initialize(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NOT_NULL(
	 "boot_record",
	 boot_record );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsmbr_boot_record_read_data(
	          boot_record,
	          vsmbr_test_boot_record_data1,
	          512,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSMBR_TEST_RUN_WITH_ARGS(
	 "libvsmbr_boot_record_get_number_of_partition_entries",
	 vsmbr_test_boot_record_get_number_of_partition_entries,
	 boot_record );

	VSMBR_TEST_RUN_WITH_ARGS(
	 "libvsmbr_boot_record_get_partition_entry_by_index",
	 vsmbr_test_boot_record_get_partition_entry_by_index,
	 boot_record );

	/* Clean up
	 */
	result = libvsmbr_boot_record_free(
	          &boot_record,
	          &error );

	VSMBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "boot_record",
	 boot_record );

	VSMBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT )
on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( boot_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &boot_record,
		 NULL );
	}
	return( EXIT_FAILURE );
#endif /* defined( __GNUC__ ) && !defined( LIBVSMBR_DLL_IMPORT ) */
}

