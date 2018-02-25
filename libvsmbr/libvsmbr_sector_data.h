/*
 * Chunk data functions
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

#if !defined( _LIBVSMBR_SECTOR_DATA_H )
#define _LIBVSMBR_SECTOR_DATA_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_sector_data libvsmbr_sector_data_t;

struct libvsmbr_sector_data
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libvsmbr_sector_data_initialize(
     libvsmbr_sector_data_t **sector_data,
     size_t data_size,
     libcerror_error_t **error );

int libvsmbr_sector_data_free(
     libvsmbr_sector_data_t **sector_data,
     libcerror_error_t **error );

int libvsmbr_sector_data_read_file_io_handle(
     libvsmbr_sector_data_t *sector_data,
     libbfio_handle_t *file_io_handle,
     off64_t sector_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_SECTOR_DATA_H ) */

