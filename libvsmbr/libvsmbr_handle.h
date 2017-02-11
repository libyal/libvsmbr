/*
 * The internal handle functions
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVSMBR_INTERNAL_HANDLE_H )
#define _LIBVSMBR_INTERNAL_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvsmbr_extern.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcdata.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_internal_handle libvsmbr_internal_handle_t;

struct libvsmbr_internal_handle
{
	/* The partitions array
	 */
	libcdata_array_t *partitions_array;

	/* The sections array
	 */
	libcdata_array_t *sections_array;

	/* The IO handle
	 */
	libvsmbr_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;
};

LIBVSMBR_EXTERN \
int libvsmbr_handle_initialize(
     libvsmbr_handle_t **handle,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_handle_free(
     libvsmbr_handle_t **handle,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_handle_signal_abort(
     libvsmbr_handle_t *handle,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_handle_open(
     libvsmbr_handle_t *handle,
     char const *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBVSMBR_EXTERN \
int libvsmbr_handle_open_wide(
     libvsmbr_handle_t *handle,
     wchar_t const *filename,
     int access_flags,
     libcerror_error_t **error );
#endif

LIBVSMBR_EXTERN \
int libvsmbr_handle_open_file_io_handle(
     libvsmbr_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_handle_close(
     libvsmbr_handle_t *handle,
     libcerror_error_t **error );

int libvsmbr_handle_open_read(
     libvsmbr_internal_handle_t *internal_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

