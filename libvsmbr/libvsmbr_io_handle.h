/*
 * The IO handle functions
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

#if !defined( _LIBVSMBR_IO_HANDLE_H )
#define _LIBVSMBR_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcdata.h"
#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_io_handle libvsmbr_io_handle_t;

struct libvsmbr_io_handle
{
	/* The number of bytes per sector
	 */
	size_t bytes_per_sector;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libvsmbr_io_handle_initialize(
     libvsmbr_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvsmbr_io_handle_free(
     libvsmbr_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvsmbr_io_handle_read_mbr(
     libvsmbr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_array_t *sections_array,
     libcdata_array_t *partitions_array,
     libcerror_error_t **error );

int libvsmbr_io_handle_read_eprs(
     libvsmbr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_array_t *sections_array,
     libcdata_array_t *partitions_array,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

