/*
 * Info handle
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "info_handle.h"
#include "vsmbrtools_libcerror.h"
#include "vsmbrtools_libclocale.h"
#include "vsmbrtools_libvsmbr.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Copies a string of a decimal value to a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int vsmbrtools_system_string_copy_from_64_bit_in_decimal(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	static char *function              = "vsmbrtools_system_string_copy_from_64_bit_in_decimal";
	size_t string_index                = 0;
	system_character_t character_value = 0;
	uint8_t maximum_string_index       = 20;
	int8_t sign                        = 1;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	*value_64bit = 0;

	if( string[ string_index ] == (system_character_t) '-' )
	{
		string_index++;
		maximum_string_index++;

		sign = -1;
	}
	else if( string[ string_index ] == (system_character_t) '+' )
	{
		string_index++;
		maximum_string_index++;
	}
	while( string_index < string_size )
	{
		if( string[ string_index ] == 0 )
		{
			break;
		}
		if( string_index > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		*value_64bit *= 10;

		if( ( string[ string_index ] >= (system_character_t) '0' )
		 && ( string[ string_index ] <= (system_character_t) '9' ) )
		{
			character_value = (system_character_t) ( string[ string_index ] - (system_character_t) '0' );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: %" PRIc_SYSTEM " at index: %d.",
			 function,
			 string[ string_index ],
			 string_index );

			return( -1 );
		}
		*value_64bit += character_value;

		string_index++;
	}
	if( sign == -1 )
	{
		*value_64bit *= (uint64_t) -1;
	}
	return( 1 );
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libvsmbr_volume_initialize(
	     &( ( *info_handle )->input_volume ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input handle.",
		 function );

		goto on_error;
	}
	( *info_handle )->bytes_per_sector = 512;
	( *info_handle )->notify_stream    = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_volume != NULL )
		{
			if( libvsmbr_volume_free(
			     &( ( *info_handle )->input_volume ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input handle.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_volume != NULL )
	{
		if( libvsmbr_volume_signal_abort(
		     info_handle->input_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input handle to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the bytes per sector
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_bytes_per_sector(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_bytes_per_sector";
	size_t string_length  = 0;
	uint64_t value_64bit  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( vsmbrtools_system_string_copy_from_64_bit_in_decimal(
	     string,
	     string_length + 1,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy string to 64-bit decimal.",
		 function );

		return( -1 );
	}
	if( ( value_64bit != 512 )
	 && ( value_64bit != 1024 )
	 && ( value_64bit != 2048 )
	 && ( value_64bit != 4096 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unuspported bytes per sector value.",
		 function );

		return( -1 );
	}
	info_handle->bytes_per_sector = (off64_t) value_64bit;

	return( 1 );
}

/* Opens the input
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvsmbr_volume_set_bytes_per_sector(
	     info_handle->input_volume,
	     info_handle->bytes_per_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bytes per sector in input handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvsmbr_volume_open_wide(
	     info_handle->input_volume,
	     filename,
	     LIBVSMBR_OPEN_READ,
	     error ) != 1 )
#else
	if( libvsmbr_volume_open(
	     info_handle->input_volume,
	     filename,
	     LIBVSMBR_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvsmbr_volume_close(
	     info_handle->input_volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the partition type
 * Returns 1 if successful or -1 on error
 */
int info_handle_partition_type_fprint(
     info_handle_t *info_handle,
     uint8_t partition_type,
     libcerror_error_t **error )
{
	const char *description = NULL;
	static char *function   = "info_handle_partition_type_fprint";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	switch( partition_type )
	{
		case 0x00:
			description = "Empty";
			break;

		case 0x01:
			description = "FAT12 (CHS)";
			break;

		case 0x02:
			description = "XENIX root";
			break;

		case 0x03:
			description = "XENIX user";
			break;

		case 0x04:
			description = "FAT16 < 32 MiB (CHS)";
			break;

		case 0x05:
			description = "Extended (CHS)";
			break;

		case 0x06:
			description = "FAT16 (CHS)";
			break;

		case 0x07:
			description = "HPFS/NTFS";
			break;

		case 0x08:
			description = "AIX";
			break;

		case 0x09:
			description = "AIX bootable";
			break;

		case 0x0a:
			description = "OS/2 Boot Manager";
			break;

		case 0x0b:
			description = "FAT32 (CHS)";
			break;

		case 0x0c:
			description = "FAT32 (LBA)";
			break;

		case 0x0e:
			description = "FAT16 (LBA)";
			break;

		case 0x0f:
			description = "Extended (LBA)";
			break;

		case 0x10:
			description = "OPUS";
			break;

		case 0x11:
			description = "Hidden FAT12 (CHS)";
			break;

		case 0x12:
			description = "Compaq diagnostics";
			break;

		case 0x14:
			description = "Hidden FAT16 < 32 MiB (CHS)";
			break;

		case 0x16:
			description = "Hidden FAT16 (CHS)";
			break;

		case 0x17:
			description = "Hidden HPFS/NTFS";
			break;

		case 0x18:
			description = "AST SmartSleep";
			break;

		case 0x1b:
			description = "Hidden FAT32 (CHS)";
			break;

		case 0x1c:
			description = "Hidden FAT32 (LBA)";
			break;

		case 0x1e:
			description = "Hidden FAT16 (LBA)";
			break;

		case 0x24:
			description = "NEC DOS";
			break;

		case 0x39:
			description = "Plan 9";
			break;

		case 0x3c:
			description = "PartitionMagic recovery";
			break;

		case 0x40:
			description = "Venix 80286";
			break;

		case 0x41:
			description = "PPC PReP Boot";
			break;

		case 0x42:
			description = "SFS / MS LDM";
			break;

		case 0x4d:
			description = "QNX4.x";
			break;

		case 0x4e:
			description = "QNX4.x 2nd part";
			break;

		case 0x4f:
			description = "QNX4.x 3rd part";
			break;

		case 0x50:
			description = "OnTrack DM";
			break;

		case 0x51:
			description = "OnTrack DM6 Aux1";
			break;

		case 0x52:
			description = "CP/M";
			break;

		case 0x53:
			description = "OnTrack DM6 Aux3";
			break;

		case 0x54:
			description = "OnTrackDM6";
			break;

		case 0x55:
			description = "EZ-Drive";
			break;

		case 0x56:
			description = "Golden Bow";
			break;

		case 0x5c:
			description = "Priam Edisk";
			break;

		case 0x61:
			description = "SpeedStor";
			break;

		case 0x63:
			description = "GNU HURD or SysV";
			break;

		case 0x64:
			description = "Novell Netware 286";
			break;

		case 0x65:
			description = "Novell Netware 386";
			break;

		case 0x70:
			description = "DiskSecure Multi-Boot";
			break;

		case 0x75:
			description = "PC/IX";
			break;

		case 0x78:
			description = "XOSL";
			break;

		case 0x80:
			description = "Old Minix";
			break;

		case 0x81:
			description = "Minix / old Linux";
			break;

		case 0x82:
			description = "Linux swap / Solaris";
			break;

		case 0x83:
			description = "Linux";
			break;

		case 0x84:
			description = "OS/2 hidden C: drive";
			break;

		case 0x85:
			description = "Linux extended";
			break;

		case 0x86:
			description = "NTFS partition set";
			break;

		case 0x87:
			description = "NTFS partition set";
			break;

		case 0x8e:
			description = "Linux LVM";
			break;

		case 0x93:
			description = "Amoeba";
			break;

		case 0x94:
			description = "Amoeba BBT";
			break;

		case 0x9f:
			description = "BSD/OS";
			break;

		case 0xa0:
			description = "IBM Thinkpad hibernation";
			break;

		case 0xa5:
			description = "FreeBSD";
			break;

		case 0xa6:
			description = "OpenBSD";
			break;

		case 0xa7:
			description = "NeXTSTEP";
			break;

		case 0xa9:
			description = "NetBSD";
			break;

		case 0xaf:
			description = "MacOS-X";
			break;

		case 0xb7:
			description = "BSDI fs";
			break;

		case 0xb8:
			description = "BSDI swap";
			break;

		case 0xbb:
			description = "Boot Wizard hidden";
			break;

		case 0xc1:
			description = "DRDOS/sec (FAT-12)";
			break;

		case 0xc4:
			description = "DRDOS/sec (FAT-16 < 32 MiB)";
			break;

		case 0xc6:
			description = "DRDOS/sec (FAT-16)";
			break;

		case 0xc7:
			description = "Syrinx";
			break;

		case 0xda:
			description = "Non-FS data";
			break;

		case 0xdb:
			description = "CP/M / CTOS / ...";
			break;

		case 0xde:
			description = "Dell Utility";
			break;

		case 0xdf:
			description = "BootIt";
			break;

		case 0xe1:
			description = "DOS access";
			break;

		case 0xe3:
			description = "DOS R/O";
			break;

		case 0xe4:
			description = "SpeedStor";
			break;

		case 0xeb:
			description = "BeOS fs";
			break;

		case 0xee:
			description = "EFI GPT protective";
			break;

		case 0xef:
			description = "EFI System (FAT)";
			break;

		case 0xf0:
			description = "Linux/PA-RISC boot";
			break;

		case 0xf1:
			description = "SpeedStor";
			break;

		case 0xf4:
			description = "SpeedStor";
			break;

		case 0xf2:
			description = "DOS secondary";
			break;

		case 0xfd:
			description = "Linux raid autodetect";
			break;

		case 0xfe:
			description = "LANstep";
			break;

		case 0xff:
			description = "BBT";
			break;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tType\t\t\t: 0x%02" PRIx8 "",
	 partition_type );

	if( description != NULL )
	{
		fprintf(
		 info_handle->notify_stream,
		 " (%s)",
		 description );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints the partition information
 * Returns 1 if successful or -1 on error
 */
int info_handle_partition_fprint(
     info_handle_t *info_handle,
     libvsmbr_partition_t *partition,
     libcerror_error_t **error )
{
	static char *function = "info_handle_partition_fprint";
	size64_t size         = 0;
	off64_t volume_offset = 0;
	uint8_t type          = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvsmbr_partition_get_type(
	     partition,
	     &type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition type.",
		 function );

		return( -1 );
	}
	if( info_handle_partition_type_fprint(
	     info_handle,
	     type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print partition type.",
		 function );

		return( -1 );
	}
	if( libvsmbr_partition_get_volume_offset(
	     partition,
	     &volume_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition offset.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tOffset\t\t\t: %" PRIi64 " (0x%08" PRIx64 ")\n",
	 volume_offset,
	 volume_offset );

	if( libvsmbr_partition_get_size(
	     partition,
	     &size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition size.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tSize\t\t\t: %" PRIu64 "\n",
	 size );

	return( 1 );
}

/* Prints the partitions information
 * Returns 1 if successful or -1 on error
 */
int info_handle_partitions_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libvsmbr_partition_t *partition = NULL;
	static char *function           = "info_handle_partitions_fprint";
	uint32_t bytes_per_sector       = 0;
	uint32_t disk_identity          = 0;
	int number_of_partitions        = 0;
	int partition_index             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Master Boot Record (MBR) information:\n" );

	if( libvsmbr_volume_get_disk_identity(
	     info_handle->input_volume,
	     &disk_identity,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve disk_ dentity.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tDisk identity\t\t: 0x%08" PRIx32 " (%" PRIu32 ")\n",
	 disk_identity,
	 disk_identity );

	if( libvsmbr_volume_get_bytes_per_sector(
	     info_handle->input_volume,
	     &bytes_per_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of bytes per sector.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tBytes per sector\t: %" PRIu32 "\n",
	 bytes_per_sector );

	if( libvsmbr_volume_get_number_of_partitions(
	     info_handle->input_volume,
	     &number_of_partitions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of partitions.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of partitions\t: %d\n",
	 number_of_partitions );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( number_of_partitions > 0 )
	{
		for( partition_index = 0;
		     partition_index < number_of_partitions;
		     partition_index++ )
		{
			fprintf(
			 info_handle->notify_stream,
			 "Partition: %d\n",
			 partition_index + 1 );

			if( libvsmbr_volume_get_partition_by_index(
			     info_handle->input_volume,
			     partition_index,
			     &partition,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve partition: %d.",
				 function,
				 partition_index );

				goto on_error;
			}
			if( info_handle_partition_fprint(
			     info_handle,
			     partition,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print partition: %d information.",
				 function,
				 partition_index );

				goto on_error;
			}
			if( libvsmbr_partition_free(
			     &partition,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free partition: %d.",
				 function,
				 partition_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\n" );
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( partition != NULL )
	{
		libvsmbr_partition_free(
		 &partition,
		 NULL );
	}
	return( -1 );
}

