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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvsmbr_chs_address.h"
#include "libvsmbr_definitions.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcdata.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcnotify.h"
#include "libvsmbr_partition_values.h"
#include "libvsmbr_section_values.h"
#include "libvsmbr_volume_type.h"

#include "vsmbr_boot_record.h"
#include "vsmbr_partition.h"

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

/* Reads a Master Boot Record (MBR)
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_io_handle_read_mbr(
     libvsmbr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_array_t *sections_array,
     libcdata_array_t *partitions_array,
     libcerror_error_t **error )
{
	libvsmbr_partition_values_t *partition_values = NULL;
	vsmbr_partition_entry_t *partition_entry      = NULL;
	uint8_t *data                                 = NULL;
	static char *function                         = "libvsmbr_io_handle_read_mbr";
	ssize_t read_count                            = 0;
	uint32_t disk_identity                        = 0;
	uint8_t partition_entry_index                 = 0;
	int entry_index                               = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libvsmbr_chs_address_t *chs_address           = NULL;
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading boot record at offset: 0\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: 0 (0x00000000).",
		 function );

		goto on_error;
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( vsmbr_boot_record_classical_t ) );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data,
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: boot record data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vsmbr_boot_record_classical_t ),
		 0 );
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

		return( -1 );
	}
/* TODO conditional */
	byte_stream_copy_to_uint32_little_endian(
	 ( (vsmbr_boot_record_modern_t *) data )->disk_identity,
	 disk_identity );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: disk identity\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 disk_identity );

		libcnotify_printf(
		 "\n" );
	}
#endif
	partition_entry = (vsmbr_partition_entry_t *) ( (vsmbr_boot_record_classical_t *) data )->partition_entries;

	for( partition_entry_index = 0;
	     partition_entry_index < 4;
	     partition_entry_index++ )
	{
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
			 "%s: partition entry: %" PRIu8 " flags\t\t\t: 0x%02" PRIx8 "\n",
			 function,
			 partition_entry_index,
			 partition_entry->flags );

			byte_stream_copy_to_uint24_little_endian(
			 partition_entry->start_address_chs,
			 value_32bit );

			if( libvsmbr_chs_address_copy_from_byte_stream(
			     chs_address,
			     partition_entry->start_address_chs,
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
			 "%s: partition entry: %" PRIu8 " CHS start address\t: 0x%06" PRIx32 " (C: %" PRIu16 ", H: %" PRIu8 ", S: %" PRIu8 ")\n",
			 function,
			 partition_entry_index,
			 value_32bit,
			 chs_address->cylinder,
			 chs_address->head,
			 chs_address->sector );

			libcnotify_printf(
			 "%s: partition entry: %" PRIu8 " type\t\t\t: 0x%02" PRIx8 " (%s)\n",
			 function,
			 partition_entry_index,
			 partition_entry->type,
			 libvsmbr_volume_type_get_description(
			  partition_entry->type ) );

			if( libvsmbr_chs_address_copy_from_byte_stream(
			     chs_address,
			     partition_entry->end_address_chs,
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
			 partition_entry->end_address_chs,
			 value_32bit );

			libcnotify_printf(
			 "%s: partition entry: %" PRIu8 " CHS end address\t\t: 0x%06" PRIx32 " (C: %" PRIu16 ", H: %" PRIu8 ", S: %" PRIu8 ")\n",
			 function,
			 partition_entry_index,
			 value_32bit,
			 chs_address->cylinder,
			 chs_address->head,
			 chs_address->sector );

			byte_stream_copy_to_uint32_little_endian(
			 partition_entry->start_address_lba,
			 value_32bit );

			libcnotify_printf(
			 "%s: partition entry: %" PRIu8 " LBA start address\t: %" PRIu32 " (0x%08" PRIx32 ")\n",
			 function,
			 partition_entry_index,
			 value_32bit,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 partition_entry->size,
			 value_32bit );

			libcnotify_printf(
			 "%s: partition entry: %" PRIu8 " size\t\t\t: %" PRIu32 "\n",
			 function,
			 partition_entry_index,
			 value_32bit );

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
		/* Ignore empty partition entries
		 */
		if( partition_entry->type != 0 )
		{
			if( libvsmbr_partition_values_initialize(
			     &partition_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create partition values.",
				 function );

				goto on_error;
			}
			partition_values->type = partition_entry->type;

			byte_stream_copy_to_uint32_little_endian(
			 partition_entry->start_address_lba,
			 partition_values->offset );

			byte_stream_copy_to_uint32_little_endian(
			 partition_entry->size,
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
		partition_entry += 1;
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
	memory_free(
	 data );

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
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
/* TODO clear partitions array */
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

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
	libvsmbr_chs_address_t *chs_address           = NULL;
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
	data = (uint8_t *) memory_allocate(
			    sizeof( vsmbr_boot_record_classical_t ) );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	while( file_offset < (off64_t) file_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading Extended Partition Record (EPR) at offset: %" PRIi64"\n",
			 function,
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
			 "%s: unable to seek offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      data,
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

			goto on_error;
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
			 0 );
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

			return( -1 );
		}
		has_extended_partition = 0;

		partition_entry = (vsmbr_partition_entry_t *) ( (vsmbr_boot_record_classical_t *) data )->partition_entries;

		for( partition_entry_index = 0;
		     partition_entry_index < 4;
		     partition_entry_index++ )
		{
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
				 "%s: partition entry: %" PRIu8 " flags\t\t: 0x%02" PRIx8 "\n",
				 function,
				 partition_entry_index,
				 partition_entry->flags );

				byte_stream_copy_to_uint24_little_endian(
				 partition_entry->start_address_chs,
				 value_32bit );

				if( libvsmbr_chs_address_copy_from_byte_stream(
				     chs_address,
				     partition_entry->start_address_chs,
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
				 "%s: partition entry: %" PRIu8 " CHS start address\t: 0x%06" PRIx32 " (C: %" PRIu16 ", H: %" PRIu8 ", S: %" PRIu8 ")\n",
				 function,
				 partition_entry_index,
				 value_32bit,
				 chs_address->cylinder,
				 chs_address->head,
				 chs_address->sector );

				libcnotify_printf(
				 "%s: partition entry: %" PRIu8 " type\t\t: 0x%02" PRIx8 " (%s)\n",
				 function,
				 partition_entry_index,
				 partition_entry->type,
				 libvsmbr_volume_type_get_description(
				  partition_entry->type ) );

				if( libvsmbr_chs_address_copy_from_byte_stream(
				     chs_address,
				     partition_entry->end_address_chs,
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
				 partition_entry->end_address_chs,
				 value_32bit );

				libcnotify_printf(
				 "%s: partition entry: %" PRIu8 " CHS end address\t: 0x%06" PRIx32 " (C: %" PRIu16 ", H: %" PRIu8 ", S: %" PRIu8 ")\n",
				 function,
				 partition_entry_index,
				 value_32bit,
				 chs_address->cylinder,
				 chs_address->head,
				 chs_address->sector );

				byte_stream_copy_to_uint32_little_endian(
				 partition_entry->start_address_lba,
				 value_32bit );

				libcnotify_printf(
				 "%s: partition entry: %" PRIu8 " LBA start address\t: %" PRIu32 " (0x%08" PRIx32 ")\n",
				 function,
				 partition_entry_index,
				 value_32bit,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 partition_entry->size,
				 value_32bit );

				libcnotify_printf(
				 "%s: partition entry: %" PRIu8 " size\t\t: %" PRIu32 "\n",
				 function,
				 partition_entry_index,
				 value_32bit );

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
					 partition_entry->size,
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
	memory_free(
	 data );

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
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
/* TODO clear partitions array */
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

