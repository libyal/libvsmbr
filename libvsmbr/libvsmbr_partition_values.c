/*
 * The partition values functions
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

#include "libvsmbr_libcerror.h"
#include "libvsmbr_partition_values.h"

/* Creates partition values
 * Make sure the value partition_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_values_initialize(
     libvsmbr_partition_values_t **partition_values,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_values_initialize";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( *partition_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition values value already set.",
		 function );

		return( -1 );
	}
	*partition_values = memory_allocate_structure(
	                     libvsmbr_partition_values_t );

	if( *partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *partition_values,
	     0,
	     sizeof( libvsmbr_partition_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition_values != NULL )
	{
		memory_free(
		 *partition_values );

		*partition_values = NULL;
	}
	return( -1 );
}

/* Frees partition values
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_values_free(
     libvsmbr_partition_values_t **partition_values,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_values_free";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( *partition_values != NULL )
	{
		memory_free(
		 *partition_values );

		*partition_values = NULL;
	}
	return( 1 );
}

/* Retrieves the partition type
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_values_get_type(
     libvsmbr_partition_values_t *partition_values,
     uint8_t *type,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_values_get_type";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = partition_values->type;

	return( 1 );
}

/* Retrieves the partition offset
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_values_get_offset(
     libvsmbr_partition_values_t *partition_values,
     off64_t *offset,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_values_get_offset";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = partition_values->offset;

	return( 1 );
}

/* Retrieves the partition size
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_values_get_size(
     libvsmbr_partition_values_t *partition_values,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_partition_values_get_size";

	if( partition_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition values.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = partition_values->size;

	return( 1 );
}

