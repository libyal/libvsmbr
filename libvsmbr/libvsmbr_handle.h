/*
 * The handle functions
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

#if !defined( _LIBVSMBR_HANDLE_H )
#define _LIBVSMBR_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvsmbr_boot_record.h"
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
	libcdata_array_t *partitions;

	/* The IO handle
	 */
	libvsmbr_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvsmbr_handle_read_partition_entries(
     libvsmbr_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libvsmbr_boot_record_t *boot_record,
     uint8_t *first_partition_entry,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_handle_get_number_of_partitions(
     libvsmbr_handle_t *handle,
     int *number_of_partitions,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_handle_get_partition_by_index(
     libvsmbr_handle_t *handle,
     int partition_index,
     libvsmbr_partition_t **partition,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_HANDLE_H ) */

