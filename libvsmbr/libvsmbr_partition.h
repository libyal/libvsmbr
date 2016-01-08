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

#if !defined( _LIBVSMBR_INTERNAL_PARTITION_H )
#define _LIBVSMBR_INTERNAL_PARTITION_H

#include <common.h>
#include <types.h>

#include "libvsmbr_extern.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_internal_partition libvsmbr_internal_partition_t;

struct libvsmbr_internal_partition
{
	/* The IO handle
	 */
	libvsmbr_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

int libvsmbr_partition_initialize(
     libvsmbr_partition_t **partition,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_partition_free(
     libvsmbr_partition_t **partition,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

