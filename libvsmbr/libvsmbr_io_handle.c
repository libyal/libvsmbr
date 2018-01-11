/*
 * The IO handle functions
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
#include <memory.h>
#include <types.h>

#include "libvsmbr_io_handle.h"
#include "libvsmbr_libcerror.h"

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_io_handle_initialize(
     libvsmbr_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libvsmbr_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libvsmbr_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		goto on_error;
	}
	( *io_handle )->bytes_per_sector = 512;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_io_handle_free(
     libvsmbr_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_io_handle_clear(
     libvsmbr_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libvsmbr_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->bytes_per_sector = 512;

	return( 1 );
}

#ifdef TODO

/* Reads Extended Partition Records (EPRs)
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_io_handle_read_eprs(
     libvsmbr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_array_t *sections_array,
     libcdata_array_t *partitions_array,
     libcerror_error_t **error )
{
	libvsmbr_boot_record_t *boot_record           = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	vsmbr_partition_entry_t *partition_entry      = NULL;
	uint8_t *data                                 = NULL;
	static char *function                         = "libvsmbr_io_handle_read_eprs";
	off64_t file_offset                           = 0;
	size64_t file_size                            = 0;
	ssize_t read_count                            = 0;
        uint8_t has_extended_partition                = 0;
	uint8_t partition_entry_index                 = 0;
	int entry_index                               = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                          = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	while( file_offset < (off64_t) file_size )
	{
			/* Ignore empty partition entries
			 */
			if( partition_entry->type != 0 )
			{
				if( partition_entry->type != 0x05 )
				{
					if( libvsmbr_partition_values_initialize(
					     &partition_values,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create sub partition values.",
						 function );

						goto on_error;
					}
					partition_values->type = partition_entry->type;

					byte_stream_copy_to_uint32_little_endian(
					 partition_entry->start_address_lba,
					 partition_values->offset );

					byte_stream_copy_to_uint32_little_endian(
					 partition_entry->number_of_sectors,
					 partition_values->size );

					partition_values->offset *= io_handle->bytes_per_sector;
					partition_values->size   *= io_handle->bytes_per_sector;

/* TODO offset and size sanity check */

					if( libcdata_array_append_entry(
					     partitions_array,
					     &entry_index,
					     (intptr_t *) partition_values,
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
					partition_values = NULL;
				}
				else
				{
					byte_stream_copy_to_uint32_little_endian(
					 partition_entry->start_address_lba,
					 file_offset );

					file_offset *= io_handle->bytes_per_sector;

fprintf( stderr, "X: %" PRIi64 ", %" PRIu64 "\n", file_offset, file_size );
/* TODO offset and size sanity check */
					has_extended_partition = 1;
				}
			}
			partition_entry += 1;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: boot signature\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
			 function,
			 ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 0 ],
			 ( (vsmbr_boot_record_classical_t *) data )->boot_signature[ 1 ] );

			libcnotify_printf(
			 "\n" );
		}
#endif
		if( has_extended_partition == 0 )
		{
			break;
		}
	}
	return( 1 );

on_error:
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	if( boot_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &boot_record,
		 NULL );
	}
	return( -1 );
}

#endif /* TODO */

