/*
 * Signal handling functions
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

#if !defined( _VSMBRTOOLS_SIGNAL_H )
#define _VSMBRTOOLS_SIGNAL_H

#include <common.h>
#include <types.h>

#include "vsmbrtools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_SIGNAL_H ) && !defined( WINAPI )
#error missing signal functions
#endif

#if defined( WINAPI )
typedef unsigned long vsmbrtools_signal_t;

#else
typedef int vsmbrtools_signal_t;

#endif /* defined( WINAPI ) */

#if defined( WINAPI )

BOOL WINAPI vsmbrtools_signal_handler(
             vsmbrtools_signal_t signal );

#if defined( _MSC_VER )

void vsmbrtools_signal_initialize_memory_debug(
      void );

#endif /* defined( _MSC_VER ) */

#endif /* defined( WINAPI ) */

int vsmbrtools_signal_attach(
     void (*signal_handler)( vsmbrtools_signal_t ),
     libcerror_error_t **error );

int vsmbrtools_signal_detach(
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSMBRTOOLS_SIGNAL_H ) */

