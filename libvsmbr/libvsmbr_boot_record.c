/*
 * The boot record functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvsmbr_boot_record.h"
#include "libvsmbr_chs_address.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcnotify.h"
#include "libvsmbr_partition_entry.h"
#include "libvsmbr_partition_values.h"

#include "vsmbr_boot_record.h"
#include "vsmbr_partition_entry.h"

/* Creates a boot record
 * Make sure the value boot_record is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_boot_record_initialize(
     libvsmbr_boot_record_t **boot_record,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_boot_record_initialize";

	if( boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid boot record.",
		 function );

		return( -1 );
	}
	if( *boot_record != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid boot record value already set.",
		 function );

		return( -1 );
	}
	*boot_record = memory_allocate_structure(
	                libvsmbr_boot_record_t );

	if( *boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create boot record.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *boot_record,
	     0,
	     sizeof( libvsmbr_boot_record_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear boot record.",
		 function );

		memory_free(
		 *boot_record );

		*boot_record = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *boot_record )->partition_entries ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create partition entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *boot_record != NULL )
	{
		memory_free(
		 *boot_record );

		*boot_record = NULL;
	}
	return( -1 );
}

/* Frees a boot record
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_boot_record_free(
     libvsmbr_boot_record_t **boot_record,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_boot_record_free";
	int result            = 1;

	if( boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid boot record.",
		 function );

		return( -1 );
	}
	if( *boot_record != NULL )
	{
		if( libcdata_array_free(
		     &( ( *boot_record )->partition_entries ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvsmbr_partition_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the partition entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *boot_record );

		*boot_record = NULL;
	}
	return( result );
}

/* Reads a boot record
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_boot_record_read_data(
     libvsmbr_boot_record_t *boot_record,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libvsmbr_partition_entry_t *partition_entry = NULL;
	static char *function                       = "libvsmbr_boot_record_read_data";
	size_t data_offset                          = 0;
	uint8_t partition_entry_index               = 0;
	int entry_index                             = 0;

	if( boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid boot record.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size != sizeof( vsmbr_boot_record_classical_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: boot record data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vsmbr_boot_record_classical_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( ( ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 0 ] != 0x55 )
	 || ( ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 1 ] != 0xaa ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid boot signature: 0x%02" PRIx8 " 0x%02", PRIx8 ".",
		 function,
		 ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 0 ],
		 ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 1 ] );

		goto on_error;
	}
/* TODO make conditional */
	byte_stream_copy_to_uint32_little_endian(
	 ( (vsmbr_boot_record_modern_t *) data )->disk_identity,
	 boot_record->disk_identity );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: disk identity\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 boot_record->disk_identity );

		libcnotify_printf(
		 "\n" );
	}
#endif
	data_offset = 446;

	for( partition_entry_index = 0;
	     partition_entry_index < 4;
	     partition_entry_index++ )
	{
		if( libvsmbr_partition_entry_initialize(
		     &partition_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create partition entry.",
			 function );

			goto on_error;
		}
		partition_entry->index = partition_entry_index;

		if( libvsmbr_partition_entry_read_data(
		     partition_entry,
		     &( data[ data_offset ] ),
		     sizeof( vsmbr_partition_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read partition entry data.",
			 function );

			goto on_error;
		}
		data_offset += sizeof( vsmbr_partition_entry_t );

		if( libcdata_array_append_entry(
		     boot_record->partition_entries,
		     &entry_index,
		     (intptr_t *) partition_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append partition entry: %" PRIu8 " to array.",
			 function,
			 partition_entry_index );

			goto on_error;
		}
		partition_entry = NULL;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: boot signature\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 0 ],
		 ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 1 ] );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( partition_entry != NULL )
	{
		libvsmbr_partition_entry_free(
		 &partition_entry,
		 NULL );
	}
	libcdata_array_empty(
	 boot_record->partition_entries,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvsmbr_partition_entry_free,
	 NULL );

	return( -1 );
}

/* Reads a boot record
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_boot_record_read_file_io_handle(
     libvsmbr_boot_record_t *boot_record,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t boot_record_data[ sizeof( vsmbr_boot_record_classical_t ) ];

	static char *function = "libvsmbr_boot_record_read_file_io_handle";
	ssize_t read_count    = 0;

	if( boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid boot record.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading boot record at offset: %" PRIu64 " (0x%08" PRIx64 ").\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: %" PRIu64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              boot_record_data,
	              sizeof( vsmbr_boot_record_classical_t ),
	              error );

	if( read_count != (ssize_t) sizeof( vsmbr_boot_record_classical_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read boot record data.",
		 function );

		return( -1 );
	}
	if( libvsmbr_boot_record_read_data(
	     boot_record,
	     boot_record_data,
	     sizeof( vsmbr_boot_record_classical_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read boot record data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of partition entries
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_boot_record_get_number_of_partition_entries(
     libvsmbr_boot_record_t *boot_record,
     int *number_of_partition_entries,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_boot_record_get_number_of_partition_entries";

	if( boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid boot record.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     boot_record->partition_entries,
	     number_of_partition_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of partition entries from array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific partition entry
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_boot_record_get_partition_entry_by_index(
     libvsmbr_boot_record_t *boot_record,
     int partition_entry_index,
     libvsmbr_partition_entry_t **partition_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_boot_record_get_partition_entry_by_index";

	if( boot_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid boot record.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     boot_record->partition_entries,
	     partition_entry_index,
	     (intptr_t **) partition_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition entry: %d from array.",
		 function,
		 partition_entry_index );

		return( -1 );
	}
	return( 1 );
}

