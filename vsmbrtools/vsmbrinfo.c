/*
 * Shows information obtained from a Master Boot Record (MBR) volume system
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

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "info_handle.h"
#include "vsmbrtools_getopt.h"
#include "vsmbrtools_libcerror.h"
#include "vsmbrtools_libclocale.h"
#include "vsmbrtools_libcnotify.h"
#include "vsmbrtools_libvsmbr.h"
#include "vsmbrtools_output.h"
#include "vsmbrtools_signal.h"
#include "vsmbrtools_unused.h"

info_handle_t *vsmbrinfo_info_handle = NULL;
int vsmbrinfo_abort                  = 0;

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use vsmbrinfo to determine information about a Master Boot Record\n"
	                 "(MBR) volume system.\n\n" );

	fprintf( stream, "Usage: vsmbrinfo [ -b bytes_per_sector ] [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-b:     specify the number of bytes per sector (default is 512)\n"
	                 "\t        (use this to override the automatic bytes per sector detection)\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Signal handler for vsmbrinfo
 */
void vsmbrinfo_signal_handler(
      vsmbrtools_signal_t signal VSMBRTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vsmbrinfo_signal_handler";

	VSMBRTOOLS_UNREFERENCED_PARAMETER( signal )

	vsmbrinfo_abort = 1;

	if( vsmbrinfo_info_handle != NULL )
	{
		if( info_handle_signal_abort(
		     vsmbrinfo_info_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal info handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error                    = NULL;
	system_character_t *option_bytes_per_sector = NULL;
	system_character_t *source                  = NULL;
	char *program                               = "vsmbrinfo";
	system_integer_t option                     = 0;
	int result                                  = 0;
	int verbose                                 = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "vsmbrtools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( vsmbrtools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	vsmbrtools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = vsmbrtools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "b:hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'b':
				option_bytes_per_sector = optarg;

				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				vsmbrtools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libvsmbr_notify_set_stream(
	 stderr,
	 NULL );
	libvsmbr_notify_set_verbose(
	 verbose );

	if( info_handle_initialize(
	     &vsmbrinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize info handle.\n" );

		goto on_error;
	}
	if( option_bytes_per_sector != NULL )
	{
		result = info_handle_set_bytes_per_sector(
			  vsmbrinfo_info_handle,
			  option_bytes_per_sector,
			  &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set bytes per sector.\n" );

			goto on_error;
		}
		else if( result == 0 )
		{
			fprintf(
			 stderr,
			 "Unsupported bytes per sector defaulting to: %" PRIu32 ".\n",
			 vsmbrinfo_info_handle->bytes_per_sector );
		}
	}
	if( info_handle_open_input(
	     vsmbrinfo_info_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	if( info_handle_partitions_fprint(
	     vsmbrinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print partitions information.\n" );

		goto on_error;
	}
	if( info_handle_close_input(
	     vsmbrinfo_info_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close info handle.\n" );

		goto on_error;
	}
	if( info_handle_free(
	     &vsmbrinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free info handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( vsmbrinfo_info_handle != NULL )
	{
		info_handle_free(
		 &vsmbrinfo_info_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

