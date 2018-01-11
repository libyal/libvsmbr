/*
 * The partition entry functions
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

#include "libvsmbr_chs_address.h"
#include "libvsmbr_debug.h"
#include "libvsmbr_definitions.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcnotify.h"
#include "libvsmbr_partition_entry.h"
#include "libvsmbr_volume_type.h"

#include "vsmbr_partition_entry.h"

/* Creates a partition entry
 * Make sure the value partition_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_entry_initialize(
     libvsmbr_partition_entry_t **partition_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_entry_initialize";

	if( partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition entry.",
		 function );

		return( -1 );
	}
	if( *partition_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition entry value already set.",
		 function );

		return( -1 );
	}
	*partition_entry = memory_allocate_structure(
	                    libvsmbr_partition_entry_t );

	if( *partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *partition_entry,
	     0,
	     sizeof( libvsmbr_partition_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition_entry != NULL )
	{
		memory_free(
		 *partition_entry );

		*partition_entry = NULL;
	}
	return( -1 );
}

/* Frees a partition entry
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_entry_free(
     libvsmbr_partition_entry_t **partition_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_entry_free";

	if( partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition entry.",
		 function );

		return( -1 );
	}
	if( *partition_entry != NULL )
	{
		memory_free(
		 *partition_entry );

		*partition_entry = NULL;
	}
	return( 1 );
}

/* Reads a partition entry
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_entry_read_data(
     libvsmbr_partition_entry_t *partition_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function               = "libvsmbr_partition_entry_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	libvsmbr_chs_address_t *chs_address = NULL;
	uint32_t value_32bit                = 0;
#endif

	if( partition_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition entry.",
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
	if( data_size != sizeof( vsmbr_partition_entry_t) )
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
		 "%s: entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vsmbr_partition_entry_t ),
		 0 );
	}
#endif
	partition_entry->flags = ( (vsmbr_partition_entry_t *) data )->flags;

	partition_entry->type = ( (vsmbr_partition_entry_t *) data )->type;

	byte_stream_copy_to_uint32_little_endian(
	 ( (vsmbr_partition_entry_t *) data )->start_address_lba,
	 partition_entry->start_address_lba );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vsmbr_partition_entry_t *) data )->number_of_sectors,
	 partition_entry->number_of_sectors );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libvsmbr_chs_address_initialize(
		     &chs_address,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create CHS address.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: entry: %" PRIu8 " flags\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 partition_entry->index,
		 partition_entry->flags );
		libvsmbr_debug_print_partition_entry_flags(
		 partition_entry->flags );
		libcnotify_printf(
		 "\n" );

		byte_stream_copy_to_uint24_little_endian(
		 ( (vsmbr_partition_entry_t *) data )->start_address_chs,
		 value_32bit );

		if( libvsmbr_chs_address_copy_from_byte_stream(
		     chs_address,
		     ( (vsmbr_partition_entry_t *) data )->start_address_chs,
		     3,
		     LIBVSMBR_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy CHS address from byte stream.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: entry: %" PRIu8 " CHS start address\t\t: 0x%06" PRIx32 " (C: %" PRIu16 ", H: %" PRIu8 ", S: %" PRIu8 ")\n",
		 function,
		 partition_entry->index,
		 value_32bit,
		 chs_address->cylinder,
		 chs_address->head,
		 chs_address->sector );

		libcnotify_printf(
		 "%s: entry: %" PRIu8 " type\t\t\t: 0x%02" PRIx8 " (%s)\n",
		 function,
		 partition_entry->index,
		 partition_entry->type,
		 libvsmbr_volume_type_get_description(
		  partition_entry->type ) );

		if( libvsmbr_chs_address_copy_from_byte_stream(
		     chs_address,
		     ( (vsmbr_partition_entry_t *) data )->end_address_chs,
		     3,
		     LIBVSMBR_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy CHS address from byte stream.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint24_little_endian(
		 ( (vsmbr_partition_entry_t *) data )->end_address_chs,
		 value_32bit );

		libcnotify_printf(
		 "%s: entry: %" PRIu8 " CHS end address\t\t: 0x%06" PRIx32 " (C: %" PRIu16 ", H: %" PRIu8 ", S: %" PRIu8 ")\n",
		 function,
		 partition_entry->index,
		 value_32bit,
		 chs_address->cylinder,
		 chs_address->head,
		 chs_address->sector );

		libcnotify_printf(
		 "%s: entry: %" PRIu8 " LBA start address\t\t: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 partition_entry->index,
		 partition_entry->start_address_lba,
		 partition_entry->start_address_lba );

		libcnotify_printf(
		 "%s: entry: %" PRIu8 " number of sectors\t\t: %" PRIu32 "\n",
		 function,
		 partition_entry->index,
		 partition_entry->number_of_sectors );

		libcnotify_printf(
		 "\n" );

		if( libvsmbr_chs_address_free(
		     &chs_address,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free CHS address.",
			 function );

			goto on_error;
		}
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( chs_address != NULL )
	{
		libvsmbr_chs_address_free(
		 &chs_address,
		 NULL );
	}
#endif
	return( -1 );
}

