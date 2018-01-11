/*
 * The boot record functions
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

#if !defined( _LIBVSMBR_BOOT_RECORD_H )
#define _LIBVSMBR_BOOT_RECORD_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_boot_record libvsmbr_boot_record_t;

struct libvsmbr_boot_record
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

int libvsmbr_boot_record_initialize(
     libvsmbr_boot_record_t **boot_record,
     libcerror_error_t **error );

int libvsmbr_boot_record_free(
     libvsmbr_boot_record_t **boot_record,
     libcerror_error_t **error );

int libvsmbr_boot_record_read_file_io_handle(
     libvsmbr_boot_record_t *boot_record,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvsmbr_boot_record_read_data(
     libvsmbr_boot_record_t *boot_record,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_BOOT_RECORD_H ) */

