/*
 * The section values functions
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
#include "libvsmbr_section_values.h"

/* Creates section values
 * Make sure the value section_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_section_values_initialize(
     libvsmbr_section_values_t **section_values,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_section_values_initialize";

	if( section_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section values.",
		 function );

		return( -1 );
	}
	if( *section_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid section values value already set.",
		 function );

		return( -1 );
	}
	*section_values = memory_allocate_structure(
	                   libvsmbr_section_values_t );

	if( *section_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create section values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *section_values,
	     0,
	     sizeof( libvsmbr_section_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear section values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *section_values != NULL )
	{
		memory_free(
		 *section_values );

		*section_values = NULL;
	}
	return( -1 );
}

/* Frees section values
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_section_values_free(
     libvsmbr_section_values_t **section_values,
     libcerror_error_t **error )
{
	static char *function = "libvsmbr_section_values_free";

	if( section_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section values.",
		 function );

		return( -1 );
	}
	if( *section_values != NULL )
	{
		memory_free(
		 *section_values );

		*section_values = NULL;
	}
	return( 1 );
}

