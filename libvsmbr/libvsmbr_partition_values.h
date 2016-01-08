/*
 * The partition values functions
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

#if !defined( _LIBVSMBR_PARTITION_VALUES_H )
#define _LIBVSMBR_PARTITION_VALUES_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcdata.h"
#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_partition_values libvsmbr_partition_values_t;

struct libvsmbr_partition_values
{
	/* The type
	 */
	uint8_t type;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;
};

int libvsmbr_partition_values_initialize(
     libvsmbr_partition_values_t **partition_values,
     libcerror_error_t **error );

int libvsmbr_partition_values_free(
     libvsmbr_partition_values_t **partition_values,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

