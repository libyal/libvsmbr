/*
 * Python object wrapper of libvsmbr_handle_t
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

#if !defined( _PYVSMBR_HANDLE_H )
#define _PYVSMBR_HANDLE_H

#include <common.h>
#include <types.h>

#include "pyvsmbr_libbfio.h"
#include "pyvsmbr_libvsmbr.h"
#include "pyvsmbr_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsmbr_handle pyvsmbr_handle_t;

struct pyvsmbr_handle
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsmbr handle
	 */
	libvsmbr_handle_t *handle;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyvsmbr_handle_object_methods[];
extern PyTypeObject pyvsmbr_handle_type_object;

PyObject *pyvsmbr_handle_new(
           void );

PyObject *pyvsmbr_handle_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_handle_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyvsmbr_handle_init(
     pyvsmbr_handle_t *pyvsmbr_handle );

void pyvsmbr_handle_free(
      pyvsmbr_handle_t *pyvsmbr_handle );

PyObject *pyvsmbr_handle_signal_abort(
           pyvsmbr_handle_t *pyvsmbr_handle,
           PyObject *arguments );

PyObject *pyvsmbr_handle_open(
           pyvsmbr_handle_t *pyvsmbr_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_handle_open_file_object(
           pyvsmbr_handle_t *pyvsmbr_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_handle_close(
           pyvsmbr_handle_t *pyvsmbr_handle,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSMBR_HANDLE_H ) */

