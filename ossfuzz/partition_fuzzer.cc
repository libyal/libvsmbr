/*
 * OSS-Fuzz target for libvsmbr partition type
 *
 * Copyright (C) 2019-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libvsmbr.h"

#if !defined( LIBVSMBR_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_open_file_io_handle(
     libvsmbr_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsmbr_error_t **error );

#endif /* !defined( LIBVSMBR_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t buffer[ 512 ];

	libbfio_handle_t *file_io_handle = NULL;
	libvsmbr_partition_t *partition  = NULL;
	libvsmbr_volume_t *volume        = NULL;
	off64_t partition_offset         = 0;
	off64_t volume_offset            = 0;
	size64_t partition_size          = 0;
	uint8_t value_8bit               = 0;
	int number_of_partitions         = 0;
	int read_iterator                = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvsmbr_volume_initialize(
	     &volume,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvsmbr_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     LIBVSMBR_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libvsmbr_volume;
	}
	if( libvsmbr_volume_get_number_of_partitions(
	     volume,
	     &number_of_partitions,
	     NULL ) != 1 )
	{
		goto on_error_libvsmbr_volume;
	}
	if( number_of_partitions > 0 )
	{
		if( libvsmbr_volume_get_partition_by_index(
		     volume,
		     0,
		     &partition,
		     NULL ) != 1 )
		{
			goto on_error_libvsmbr_volume;
		}
		if( libvsmbr_partition_get_type(
		     partition,
		     &value_8bit,
		     NULL ) != 1 )
		{
			goto on_error_libvsmbr_partition;
		}
		if( libvsmbr_partition_get_volume_offset(
		     partition,
		     &volume_offset,
		     NULL ) != 1 )
		{
			goto on_error_libvsmbr_partition;
		}
		if( libvsmbr_partition_get_size(
		     partition,
		     &partition_size,
		     NULL ) != 1 )
		{
			goto on_error_libvsmbr_partition;
		}
		for( read_iterator = 0;
		     read_iterator < 128;
		     read_iterator++ )
		{
			if( partition_offset >= partition_size )
			{
				break;
			}
			if( libvsmbr_partition_read_buffer_at_offset(
			     partition,
			     buffer,
			     497,
			     partition_offset,
			     NULL ) == -1 )
			{
				goto on_error_libvsmbr_partition;
			}
			partition_offset += 497;
		}
on_error_libvsmbr_partition:
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	libvsmbr_volume_close(
	 volume,
	 NULL );

on_error_libvsmbr_volume:
	libvsmbr_volume_free(
	 &volume,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */

