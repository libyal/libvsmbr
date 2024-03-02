/*
 * Python object wrapper of libvsmbr_partition_t
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

#if !defined( _PYVSMBR_PARTITION_H )
#define _PYVSMBR_PARTITION_H

#include <common.h>
#include <types.h>

#include "pyvsmbr_libvsmbr.h"
#include "pyvsmbr_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsmbr_partition pyvsmbr_partition_t;

struct pyvsmbr_partition
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsmbr partition
	 */
	libvsmbr_partition_t *partition;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyvsmbr_partition_object_methods[];
extern PyTypeObject pyvsmbr_partition_type_object;

PyObject *pyvsmbr_partition_new(
           libvsmbr_partition_t *partition,
           PyObject *parent_object );

int pyvsmbr_partition_init(
     pyvsmbr_partition_t *pyvsmbr_partition );

void pyvsmbr_partition_free(
      pyvsmbr_partition_t *pyvsmbr_partition );

PyObject *pyvsmbr_partition_get_type(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments );

PyObject *pyvsmbr_partition_get_volume_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments );

PyObject *pyvsmbr_partition_read_buffer(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_partition_read_buffer_at_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_partition_seek_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_partition_get_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments );

PyObject *pyvsmbr_partition_get_size(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSMBR_PARTITION_H ) */

