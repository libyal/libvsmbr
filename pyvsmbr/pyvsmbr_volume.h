/*
 * Python object wrapper of libvsmbr_volume_t
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

#if !defined( _PYVSMBR_VOLUME_H )
#define _PYVSMBR_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyvsmbr_libbfio.h"
#include "pyvsmbr_libvsmbr.h"
#include "pyvsmbr_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsmbr_volume pyvsmbr_volume_t;

struct pyvsmbr_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsmbr volume
	 */
	libvsmbr_volume_t *volume;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyvsmbr_volume_object_methods[];
extern PyTypeObject pyvsmbr_volume_type_object;

int pyvsmbr_volume_init(
     pyvsmbr_volume_t *pyvsmbr_volume );

void pyvsmbr_volume_free(
      pyvsmbr_volume_t *pyvsmbr_volume );

PyObject *pyvsmbr_volume_signal_abort(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments );

PyObject *pyvsmbr_volume_open(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_volume_open_file_object(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_volume_close(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments );

PyObject *pyvsmbr_volume_get_bytes_per_sector(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments );

PyObject *pyvsmbr_volume_get_disk_identity(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments );

PyObject *pyvsmbr_volume_get_number_of_partitions(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments );

PyObject *pyvsmbr_volume_get_partition_by_index(
           PyObject *pyvsmbr_volume,
           int partition_index );

PyObject *pyvsmbr_volume_get_partition(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsmbr_volume_get_partitions(
           pyvsmbr_volume_t *pyvsmbr_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSMBR_VOLUME_H ) */

