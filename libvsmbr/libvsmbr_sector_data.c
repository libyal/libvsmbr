/*
 * Chunk data functions
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
#include <memory.h>
#include <types.h>

#include "libvsmbr_definitions.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcnotify.h"
#include "libvsmbr_libfdata.h"
#include "libvsmbr_sector_data.h"
#include "libvsmbr_unused.h"

/* Creates a sector data
 * Make sure the value sector_data is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_sector_data_initialize(
     libvsmbr_sector_data_t **sector_data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_sector_data_initialize";

	if( sector_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector data.",
		 function );

		return( -1 );
	}
	if( *sector_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sector data value already set.",
		 function );

		return( -1 );
	}
	if( ( data_size == 0 )
	 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	*sector_data = memory_allocate_structure(
	                libvsmbr_sector_data_t );

	if( *sector_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sector data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *sector_data,
	     0,
	     sizeof( libvsmbr_sector_data_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear sector data.",
		 function );

		memory_free(
		 *sector_data );

		*sector_data = NULL;

		return( -1 );
	}
	( *sector_data )->data = (uint8_t *) memory_allocate(
	                                      sizeof( uint8_t ) * data_size );

	if( ( *sector_data )->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	( *sector_data )->data_size = data_size;

	return( 1 );

on_error:
	if( *sector_data != NULL )
	{
		memory_free(
		 *sector_data );

		*sector_data = NULL;
	}
	return( -1 );
}

/* Frees a sector data
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_sector_data_free(
     libvsmbr_sector_data_t **sector_data,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_sector_data_free";
	int result            = 1;

	if( sector_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector data.",
		 function );

		return( -1 );
	}
	if( *sector_data != NULL )
	{
		if( memory_set(
		     ( *sector_data )->data,
		     0,
		     ( *sector_data )->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear data.",
			 function );

			result = -1;
		}
		memory_free(
		 ( *sector_data )->data );

		memory_free(
		 *sector_data );

		*sector_data = NULL;
	}
	return( result );
}

/* Reads sector data
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_sector_data_read_file_io_handle(
     libvsmbr_sector_data_t *sector_data,
     libbfio_handle_t *file_io_handle,
     off64_t sector_offset,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_sector_data_read_file_io_handle";
	ssize_t read_count    = 0;

	if( sector_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector data.",
		 function );

		return( -1 );
	}
	if( sector_data->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid sector data - missing data.",
		 function );

		return( -1 );
	}
	if( ( sector_data->data_size == 0 )
	 || ( sector_data->data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sector data - data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading sector data at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 sector_offset,
		 sector_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
		      file_io_handle,
		      sector_data->data,
		      sector_data->data_size,
		      sector_offset,
		      error );

	if( read_count != (ssize_t) sector_data->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sector data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 sector_offset,
		 sector_offset );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sector data:\n",
		 function );
		libcnotify_print_data(
		 sector_data->data,
		 sector_data->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	return( 1 );
}

/* Reads sector data
 * Callback function for the sector data vector
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_read_element_data(
     intptr_t *data_handle LIBVSMBR_ATTRIBUTE_UNUSED,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index LIBVSMBR_ATTRIBUTE_UNUSED,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBVSMBR_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBVSMBR_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvsmbr_sector_data_t *sector_data = NULL;
	static char *function               = "libvsmbr_partition_read_element_data";

	LIBVSMBR_UNREFERENCED_PARAMETER( data_handle );
	LIBVSMBR_UNREFERENCED_PARAMETER( element_data_file_index );
	LIBVSMBR_UNREFERENCED_PARAMETER( element_data_flags );
	LIBVSMBR_UNREFERENCED_PARAMETER( read_flags );

	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( libvsmbr_sector_data_initialize(
	     &sector_data,
	     (size_t) element_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector data.",
		 function );

		goto on_error;
	}
	if( libvsmbr_sector_data_read_file_io_handle(
	     sector_data,
	     file_io_handle,
             element_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sector data.",
		 function );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) sector_data,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvsmbr_sector_data_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set sector data as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sector_data != NULL )
	{
		libvsmbr_sector_data_free(
		 &sector_data,
		 NULL );
	}
	return( -1 );
}

