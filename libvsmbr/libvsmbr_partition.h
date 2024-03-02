/*
 * The partition functions
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

#if !defined( _LIBVSMBR_PARTITION_H )
#define _LIBVSMBR_PARTITION_H

#include <common.h>
#include <types.h>

#include "libvsmbr_extern.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcthreads.h"
#include "libvsmbr_libfcache.h"
#include "libvsmbr_libfdata.h"
#include "libvsmbr_partition_values.h"
#include "libvsmbr_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_internal_partition libvsmbr_internal_partition_t;

struct libvsmbr_internal_partition
{
	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The partition values
	 */
	libvsmbr_partition_values_t *partition_values;

	/* The sectors vector
	 */
	libfdata_vector_t *sectors_vector;

	/* The sectors cache
	 */
	libfcache_cache_t *sectors_cache;

	/* The current offset
	 */
	off64_t current_offset;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libvsmbr_partition_initialize(
     libvsmbr_partition_t **partition,
     libvsmbr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libvsmbr_partition_values_t *partition_values,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_partition_free(
     libvsmbr_partition_t **partition,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_partition_get_type(
     libvsmbr_partition_t *partition,
     uint8_t *type,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_partition_get_volume_offset(
     libvsmbr_partition_t *partition,
     off64_t *volume_offset,
     libcerror_error_t **error );

ssize_t libvsmbr_internal_partition_read_buffer_from_file_io_handle(
         libvsmbr_internal_partition_t *internal_partition,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSMBR_EXTERN \
ssize_t libvsmbr_partition_read_buffer(
         libvsmbr_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSMBR_EXTERN \
ssize_t libvsmbr_partition_read_buffer_at_offset(
         libvsmbr_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libvsmbr_internal_partition_seek_offset(
         libvsmbr_internal_partition_t *internal_partition,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSMBR_EXTERN \
off64_t libvsmbr_partition_seek_offset(
         libvsmbr_partition_t *partition,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_partition_get_offset(
     libvsmbr_partition_t *partition,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSMBR_EXTERN \
int libvsmbr_partition_get_size(
     libvsmbr_partition_t *partition,
     size64_t *size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_PARTITION_H ) */

