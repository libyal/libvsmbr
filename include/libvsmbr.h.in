/*
 * Library to access the Master Boot Record (MBR) volume system
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

#if !defined( _LIBVSMBR_H )
#define _LIBVSMBR_H

#include <libvsmbr/codepage.h>
#include <libvsmbr/definitions.h>
#include <libvsmbr/error.h>
#include <libvsmbr/extern.h>
#include <libvsmbr/features.h>
#include <libvsmbr/types.h>

#include <stdio.h>

#if defined( LIBVSMBR_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBVSMBR_EXTERN \
const char *libvsmbr_get_version(
             void );

/* Returns the access flags for reading
 */
LIBVSMBR_EXTERN \
int libvsmbr_get_access_flags_read(
     void );

/* Returns the access flags for reading and writing
 */
LIBVSMBR_EXTERN \
int libvsmbr_get_access_flags_read_write(
     void );

/* Returns the access flags for writing
 */
LIBVSMBR_EXTERN \
int libvsmbr_get_access_flags_write(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_get_codepage(
     int *codepage,
     libvsmbr_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_set_codepage(
     int codepage,
     libvsmbr_error_t **error );

/* Determines if a volume contains a Master Boot Record (MBR) signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_check_volume_signature(
     const char *filename,
     libvsmbr_error_t **error );

#if defined( LIBVSMBR_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a volume contains a Master Boot Record (MBR) signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_check_volume_signature_wide(
     const wchar_t *filename,
     libvsmbr_error_t **error );

#endif /* defined( LIBVSMBR_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSMBR_HAVE_BFIO )

/* Determines if a volume contains a Master Boot Record (MBR) signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvsmbr_error_t **error );

#endif /* defined( LIBVSMBR_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBVSMBR_EXTERN \
void libvsmbr_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_notify_set_stream(
     FILE *stream,
     libvsmbr_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_notify_stream_open(
     const char *filename,
     libvsmbr_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_notify_stream_close(
     libvsmbr_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBVSMBR_EXTERN \
void libvsmbr_error_free(
      libvsmbr_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_error_fprint(
     libvsmbr_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_error_sprint(
     libvsmbr_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_error_backtrace_fprint(
     libvsmbr_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_error_backtrace_sprint(
     libvsmbr_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Volume functions
 * ------------------------------------------------------------------------- */

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_initialize(
     libvsmbr_volume_t **volume,
     libvsmbr_error_t **error );

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_free(
     libvsmbr_volume_t **volume,
     libvsmbr_error_t **error );

/* Signals a volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_signal_abort(
     libvsmbr_volume_t *volume,
     libvsmbr_error_t **error );

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_open(
     libvsmbr_volume_t *volume,
     const char *filename,
     int access_flags,
     libvsmbr_error_t **error );

#if defined( LIBVSMBR_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_open_wide(
     libvsmbr_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libvsmbr_error_t **error );

#endif /* defined( LIBVSMBR_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSMBR_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_open_file_io_handle(
     libvsmbr_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsmbr_error_t **error );

#endif /* defined( LIBVSMBR_HAVE_BFIO ) */

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_close(
     libvsmbr_volume_t *volume,
     libvsmbr_error_t **error );

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_get_bytes_per_sector(
     libvsmbr_volume_t *volume,
     uint32_t *bytes_per_sector,
     libvsmbr_error_t **error );

/* Sets the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_set_bytes_per_sector(
     libvsmbr_volume_t *volume,
     uint32_t bytes_per_sector,
     libvsmbr_error_t **error );

/* Retrieves the disk identity (or disk identifier)
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_get_disk_identity(
     libvsmbr_volume_t *volume,
     uint32_t *disk_identity,
     libvsmbr_error_t **error );

/* Retrieves the number of partitions
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_get_number_of_partitions(
     libvsmbr_volume_t *volume,
     int *number_of_partitions,
     libvsmbr_error_t **error );

/* Retrieves a specific partition
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_volume_get_partition_by_index(
     libvsmbr_volume_t *volume,
     int partition_index,
     libvsmbr_partition_t **partition,
     libvsmbr_error_t **error );

/* -------------------------------------------------------------------------
 * Partition functions
 * ------------------------------------------------------------------------- */

/* Frees a partition
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_partition_free(
     libvsmbr_partition_t **partition,
     libvsmbr_error_t **error );

/* Retrieves the partition type
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_partition_get_type(
     libvsmbr_partition_t *partition,
     uint8_t *type,
     libvsmbr_error_t **error );

/* Retrieves the partition offset relative to the start of the volume
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_partition_get_volume_offset(
     libvsmbr_partition_t *partition,
     off64_t *volume_offset,
     libvsmbr_error_t **error );

/* Reads (partition) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBVSMBR_EXTERN \
ssize_t libvsmbr_partition_read_buffer(
         libvsmbr_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         libvsmbr_error_t **error );

/* Reads (partition) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBVSMBR_EXTERN \
ssize_t libvsmbr_partition_read_buffer_at_offset(
         libvsmbr_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libvsmbr_error_t **error );

/* Seeks a certain offset of the (partition) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBVSMBR_EXTERN \
off64_t libvsmbr_partition_seek_offset(
         libvsmbr_partition_t *partition,
         off64_t offset,
         int whence,
         libvsmbr_error_t **error );

/* Retrieves the current offset
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_partition_get_offset(
     libvsmbr_partition_t *partition,
     off64_t *offset,
     libvsmbr_error_t **error );

/* Retrieves the partition size
 * Returns 1 if successful or -1 on error
 */
LIBVSMBR_EXTERN \
int libvsmbr_partition_get_size(
     libvsmbr_partition_t *partition,
     size64_t *size,
     libvsmbr_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_H ) */

