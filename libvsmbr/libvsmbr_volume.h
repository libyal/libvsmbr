/*
 * The volume functions
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBVSMBR_VOLUME_H )
#define _LIBVSMBR_VOLUME_H

#include <common.h>
#include <types.h>

#include "libvsmbr_boot_record.h"
#include "libvsmbr_extern.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcdata.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcthreads.h"
#include "libvsmbr_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_internal_volume libvsmbr_internal_volume_t;

struct libvsmbr_internal_volume
{
	/* The disk identity
	 */
	uint32_t disk_identity;

	/* The volume size
	 */
	size64_t size;

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

	/* Value to indicate if bytes per sector was set by library
	 */
	uint8_t bytes_per_sector_set_by_library;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBVSMBR_EXTERN \
int libvsmbr_volume_initialize(
     libvsmbr_volume_t **volume,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_free(
     libvsmbr_volume_t **volume,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_signal_abort(
     libvsmbr_volume_t *volume,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_open(
     libvsmbr_volume_t *volume,
     char const *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVSMBR_EXTERN \
int libvsmbr_volume_open_wide(
     libvsmbr_volume_t *volume,
     wchar_t const *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVSMBR_EXTERN \
int libvsmbr_volume_open_file_io_handle(
     libvsmbr_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_close(
     libvsmbr_volume_t *volume,
     libcerror_error_t **error );

int libvsmbr_internal_volume_open_read(
     libvsmbr_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvsmbr_internal_volume_read_partition_entries(
     libvsmbr_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libvsmbr_boot_record_t *boot_record,
     uint8_t is_master_boot_record,
     off64_t first_extended_boot_record_offset,
     int recursion_depth,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_get_bytes_per_sector(
     libvsmbr_volume_t *volume,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_set_bytes_per_sector(
     libvsmbr_volume_t *volume,
     uint32_t bytes_per_sector,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_get_disk_identity(
     libvsmbr_volume_t *volume,
     uint32_t *disk_identity,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_get_number_of_partitions(
     libvsmbr_volume_t *volume,
     int *number_of_partitions,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_volume_get_partition_by_index(
     libvsmbr_volume_t *volume,
     int partition_index,
     libvsmbr_partition_t **partition,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_VOLUME_H ) */

