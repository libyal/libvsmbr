/*
 * The volume functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libvsmbr_boot_record.h"
#include "libvsmbr_debug.h"
#include "libvsmbr_definitions.h"
#include "libvsmbr_volume.h"
#include "libvsmbr_io_handle.h"
#include "libvsmbr_libbfio.h"
#include "libvsmbr_libcerror.h"
#include "libvsmbr_libcnotify.h"
#include "libvsmbr_partition.h"
#include "libvsmbr_partition_entry.h"
#include "libvsmbr_partition_values.h"
#include "libvsmbr_section_values.h"
#include "libvsmbr_types.h"

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_initialize(
     libvsmbr_volume_t **volume,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_initialize";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( *volume != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume value already set.",
		 function );

		return( -1 );
	}
	internal_volume = memory_allocate_structure(
	                   libvsmbr_internal_volume_t );

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_volume,
	     0,
	     sizeof( libvsmbr_internal_volume_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear volume.",
		 function );

		memory_free(
		 internal_volume );

		return( -1 );
	}
	if( libvsmbr_io_handle_initialize(
	     &( internal_volume->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_volume->partitions ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create partitions array.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_volume->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	*volume = (libvsmbr_volume_t *) internal_volume;

	return( 1 );

on_error:
	if( internal_volume != NULL )
	{
		if( internal_volume->io_handle != NULL )
		{
			libvsmbr_io_handle_free(
			 &( internal_volume->io_handle ),
			 NULL );
		}
		memory_free(
		 internal_volume );
	}
	return( -1 );
}

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_free(
     libvsmbr_volume_t **volume,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_free";
	int result                                  = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( *volume != NULL )
	{
		internal_volume = (libvsmbr_internal_volume_t *) *volume;

		if( internal_volume->file_io_handle != NULL )
		{
			if( libvsmbr_volume_close(
			     *volume,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close volume.",
				 function );

				result = -1;
			}
		}
		*volume = NULL;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_volume->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		if( libcdata_array_free(
		     &( internal_volume->partitions ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvsmbr_partition_values_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free the partitions array.",
			 function );

			result = -1;
		}
		if( libvsmbr_io_handle_free(
		     &( internal_volume->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_volume );
	}
	return( result );
}

/* Signals the volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_signal_abort(
     libvsmbr_volume_t *volume,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_signal_abort";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_volume->io_handle->abort = 1;

	return( 1 );
}

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_open(
     libvsmbr_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_open";
	size_t filename_length                      = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSMBR_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSMBR_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSMBR_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libvsmbr_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume: %s.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_volume->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_open_wide(
     libvsmbr_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_open_wide";
	size_t filename_length                      = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSMBR_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSMBR_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSMBR_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libvsmbr_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume: %ls.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_volume->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a volume using a Basic File IO (bfio) volume
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_open_file_io_handle(
     libvsmbr_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_open_file_io_handle";
	int bfio_access_flags                       = 0;
	int file_io_handle_is_open                  = 0;
	int file_io_handle_opened_in_library        = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( internal_volume->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume - file IO handle value already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSMBR_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSMBR_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSMBR_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSMBR_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libvsmbr_internal_volume_open_read(
	     internal_volume,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_volume->file_io_handle                   = file_io_handle;
	internal_volume->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
int libvsmbr_volume_close(
     libvsmbr_volume_t *volume,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_close";
	int result                                  = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( internal_volume->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_volume->file_io_handle_created_in_library != 0 )
		{
			if( libvsmbr_debug_print_read_offsets(
			     internal_volume->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_volume->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_volume->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_volume->file_io_handle_opened_in_library = 0;
	}
	if( internal_volume->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_volume->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_volume->file_io_handle_created_in_library = 0;
	}
	internal_volume->file_io_handle = NULL;

	if( libvsmbr_io_handle_clear(
	     internal_volume->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear the IO handle.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_volume->partitions,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvsmbr_partition_values_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to empty the partitions array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a volume for reading
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_internal_volume_open_read(
     libvsmbr_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libvsmbr_boot_record_t *master_boot_record = NULL;
	static char *function                      = "libvsmbr_internal_volume_open_read";

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( internal_volume->size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size from file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading Master Boot Record (MBR).\n",
		 function );
	}
#endif
	if( libvsmbr_boot_record_initialize(
	     &master_boot_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create master boot record.",
		 function );

		goto on_error;
	}
	if( libvsmbr_boot_record_read_file_io_handle(
	     master_boot_record,
	     file_io_handle,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read master boot record.",
		 function );

		goto on_error;
	}
	if( libvsmbr_internal_volume_read_partition_entries(
	     internal_volume,
	     file_io_handle,
	     0,
	     master_boot_record,
	     1,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition entries.",
		 function );

		goto on_error;
	}
	if( libvsmbr_boot_record_free(
	     &master_boot_record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free master boot record.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( master_boot_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &master_boot_record,
		 NULL );
	}
	return( -1 );
}

/* Reads partition entries in a master boot record or extended partition record
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_internal_volume_read_partition_entries(
     libvsmbr_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libvsmbr_boot_record_t *boot_record,
     uint8_t is_master_boot_record,
     int recursion_depth,
     libcerror_error_t **error )
{
	libvsmbr_boot_record_t *extended_partition_record = NULL;
	libvsmbr_partition_entry_t *partition_entry       = NULL;
	libvsmbr_partition_values_t *partition_values     = NULL;
	static char *function                             = "libvsmbr_internal_volume_read_partition_entries";
	off64_t extended_partition_record_offset          = 0;
	int entry_index                                   = 0;
	int partition_entry_index                         = 0;
	int result                                        = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( ( recursion_depth < 0 )
	 || ( recursion_depth > LIBVSMBR_MAXIMUM_RECURSION_DEPTH ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid recursion depth value out of bounds.",
		 function );

		return( -1 );
	}
	for( partition_entry_index = 0;
	     partition_entry_index < 4;
	     partition_entry_index++ )
	{
		if( libvsmbr_boot_record_get_partition_entry_by_index(
		     boot_record,
		     partition_entry_index,
		     &partition_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve partition entry: %d.",
			 function,
			 partition_entry_index );

			goto on_error;
		}
		if( partition_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing partition entry: %" PRIu8 ".",
			 function,
			 partition_entry_index );

			goto on_error;
		}
		/* Ignore empty partition entries
		 */
		if( partition_entry->type == 0 )
		{
			continue;
		}
		if( partition_entry->type == 0x05 ||
			partition_entry->type == 0x0F)
		{
			if( extended_partition_record != NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: more than 1 extended partition entry per table is not supported.",
				 function );

				goto on_error;
			}
			extended_partition_record_offset = file_offset + ( partition_entry->start_address_lba * internal_volume->io_handle->bytes_per_sector );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: reading Extended Partition Record (EPR) at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
				 function,
				 extended_partition_record_offset,
				 extended_partition_record_offset );
			}
#endif
			if( libvsmbr_boot_record_initialize(
			     &extended_partition_record,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create extended partition record.",
				 function );

				goto on_error;
			}
			result = libvsmbr_boot_record_read_file_io_handle(
				  extended_partition_record,
				  file_io_handle,
				  extended_partition_record_offset,
				  error );

			/* Linux fdisk supports sector sizes of: 512, 1024, 2048, 4096
			 */
			while( ( result != 1 )
			    && ( is_master_boot_record != 0 )
			    && ( internal_volume->io_handle->bytes_per_sector < 4096 ) )
			{
				libcerror_error_free(
				 error );

				internal_volume->io_handle->bytes_per_sector *= 2;

				extended_partition_record_offset = file_offset + ( partition_entry->start_address_lba * internal_volume->io_handle->bytes_per_sector );

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: reading Extended Partition Record (EPR) at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
					 function,
					 extended_partition_record_offset,
					 extended_partition_record_offset );
				}
#endif
				result = libvsmbr_boot_record_read_file_io_handle(
					  extended_partition_record,
					  file_io_handle,
					  extended_partition_record_offset,
					  error );
			}
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read extended partition record.",
				 function );

				goto on_error;
			}
			internal_volume->bytes_per_sector_set_by_library = 1;
		}
		else
		{
/* TODO do bytes per sector check for known volume types and GPT */

			if( libvsmbr_partition_values_initialize(
			     &partition_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create partition values.",
				 function );

				goto on_error;
			}
			partition_values->type                    = partition_entry->type;
			partition_values->partition_record_offset = file_offset;
			partition_values->sector_number           = partition_entry->start_address_lba;
			partition_values->number_of_sectors       = partition_entry->number_of_sectors;

			if( libcdata_array_append_entry(
			     internal_volume->partitions,
			     &entry_index,
			     (intptr_t *) partition_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append partition to array.",
				 function );

				goto on_error;
			}
			partition_values = NULL;
		}
	}
	if( extended_partition_record != NULL )
	{
		if( ( extended_partition_record_offset == 0 )
		 || ( extended_partition_record_offset == file_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: unsupported extended partition record offset.",
			 function );

			goto on_error;
		}
		if( libvsmbr_internal_volume_read_partition_entries(
		     internal_volume,
		     file_io_handle,
		     extended_partition_record_offset,
		     extended_partition_record,
		     0,
		     recursion_depth + 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read partition entries.",
			 function );

			goto on_error;
		}
		if( libvsmbr_boot_record_free(
		     &extended_partition_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extended partition record.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( partition_values != NULL )
	{
		libvsmbr_partition_values_free(
		 &partition_values,
		 NULL );
	}
	if( extended_partition_record != NULL )
	{
		libvsmbr_boot_record_free(
		 &extended_partition_record,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_get_bytes_per_sector(
     libvsmbr_volume_t *volume,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_get_bytes_per_sector";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	if( bytes_per_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bytes per sector.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*bytes_per_sector = internal_volume->io_handle->bytes_per_sector;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Sets the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_set_bytes_per_sector(
     libvsmbr_volume_t *volume,
     uint32_t bytes_per_sector,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_set_bytes_per_sector";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_volume->bytes_per_sector_set_by_library != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: bytes per sector value already set.",
		 function );

		return( -1 );
	}
	if( ( bytes_per_sector != 512 )
	 && ( bytes_per_sector != 1024 )
	 && ( bytes_per_sector != 2048 )
	 && ( bytes_per_sector != 4096 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported bytes per sector.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	bytes_per_sector = internal_volume->io_handle->bytes_per_sector = bytes_per_sector;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the number of partitions
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_get_number_of_partitions(
     libvsmbr_volume_t *volume,
     int *number_of_partitions,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvsmbr_volume_get_number_of_partitions";
	int result                                  = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_number_of_entries(
	     internal_volume->partitions,
	     number_of_partitions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of partitions from array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves a specific partition
 * Returns 1 if successful or -1 on error
 */
int libvsmbr_volume_get_partition_by_index(
     libvsmbr_volume_t *volume,
     int partition_index,
     libvsmbr_partition_t **partition,
     libcerror_error_t **error )
{
	libvsmbr_internal_volume_t *internal_volume   = NULL;
	libvsmbr_partition_values_t *partition_values = NULL;
	static char *function                         = "libvsmbr_volume_get_partition_by_index";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvsmbr_internal_volume_t *) volume;

	if( partition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition.",
		 function );

		return( -1 );
	}
	if( *partition != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_entry_by_index(
	     internal_volume->partitions,
	     partition_index,
	     (intptr_t **) &partition_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition values: %d from array.",
		 function,
		 partition_index );

		goto on_error;
	}
	if( libvsmbr_partition_initialize(
	     partition,
	     internal_volume->io_handle,
	     internal_volume->file_io_handle,
	     partition_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create partition: %d.",
		 function,
		 partition_index );

		goto on_error;
	}
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_LIBVSMBR_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_read(
	 internal_volume->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

