/*
 * The partition functions
 *
 * Copyright (C) 2010-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include "libvsmbr_definitions.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_partition.h"
#include "libvsmbr_types.h"

/* Creates a partition
 * Make sure the value partition is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_initialize(
     libvsmbr_partition_t **partition,
     libcerror_error_t **error )
{
	libvsmbr_internal_partition_t *internal_partition = NULL;
	static char *function                             = "libvsmbr_partition_initialize";

	if( partition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition.",
		 function );

		return( -1 );
	}
	if( *partition != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition value already set.",
		 function );

		return( -1 );
	}
	internal_partition = memory_allocate_structure(
	                      libvsmbr_internal_partition_t );

	if( internal_partition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_partition,
	     0,
	     sizeof( libvsmbr_internal_partition_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition.",
		 function );

		goto on_error;
	}
	*partition = (libvsmbr_partition_t *) internal_partition;

	return( 1 );

on_error:
	if( internal_partition != NULL )
	{
		memory_free(
		 internal_partition );
	}
	return( -1 );
}

/* Frees a partition
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_partition_free(
     libvsmbr_partition_t **partition,
     libcerror_error_t **error )
{
	libvsmbr_internal_partition_t *internal_partition = NULL;
	static char *function                             = "libvsmbr_partition_free";
	int result                                        = 1;

	if( partition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition.",
		 function );

		return( -1 );
	}
	if( *partition != NULL )
	{
		internal_partition = (libvsmbr_internal_partition_t *) *partition;
		*partition         = NULL;

		memory_free(
		 internal_partition );
	}
	return( result );
}

