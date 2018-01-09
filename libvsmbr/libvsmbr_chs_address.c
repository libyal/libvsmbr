/*
 * Cylinder Head Sector (CHS) address functions
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
#include "libvsmbr_libcerror.h"

/* Creates a CHS address
 * Make sure the value chs_address is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_chs_address_initialize(
     libvsmbr_chs_address_t **chs_address,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_chs_address_initialize";

	if( chs_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid CHS address.",
		 function );

		return( -1 );
	}
	if( *chs_address != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid CHS address value already set.",
		 function );

		return( -1 );
	}
	*chs_address = memory_allocate_structure(
	                libvsmbr_chs_address_t );

	if( *chs_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create CHS address.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *chs_address,
	     0,
	     sizeof( libvsmbr_chs_address_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear CHS address.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *chs_address != NULL )
	{
		memory_free(
		 *chs_address );

		*chs_address = NULL;
	}
	return( -1 );
}

/* Frees an CHS address
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_chs_address_free(
     libvsmbr_chs_address_t **chs_address,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_chs_address_free";

	if( chs_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid CHS address.",
		 function );

		return( -1 );
	}
	if( *chs_address != NULL )
	{
		memory_free(
		 *chs_address );

		*chs_address = NULL;
	}
	return( 1 );
}

/* Converts a byte stream into a CHS address
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_chs_address_copy_from_byte_stream(
     libvsmbr_chs_address_t *chs_address,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_chs_address_copy_from_byte_stream";
	uint32_t value_32bit  = 0;

	if( chs_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid CHS address.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < 3 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBVSMBR_ENDIAN_BIG )
	 && ( byte_order != LIBVSMBR_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBVSMBR_ENDIAN_LITTLE )
	{
		byte_stream_copy_to_uint24_little_endian(
		 byte_stream,
		 value_32bit );

		byte_stream += 3;
	}
	else if( byte_order == LIBVSMBR_ENDIAN_BIG )
	{
		byte_stream_copy_to_uint24_big_endian(
		 byte_stream,
		 value_32bit );

		byte_stream += 3;
	}
	chs_address->head = (uint8_t) ( value_32bit & 0x000000ffUL );

	value_32bit >>= 8;

	chs_address->sector = (uint8_t) ( value_32bit & 0x0000003fUL );

	value_32bit >>= 6;

	chs_address->cylinder = (uint16_t) ( value_32bit & 0x000003ffUL );

	return( 1 );
}

