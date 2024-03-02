/*
 * Python object definition of the sequence and iterator object of partitions
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

#if !defined( _PYVSMBR_PARTITIONS_H )
#define _PYVSMBR_PARTITIONS_H

#include <common.h>
#include <types.h>

#include "pyvsmbr_libvsmbr.h"
#include "pyvsmbr_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsmbr_partitions pyvsmbr_partitions_t;

struct pyvsmbr_partitions
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyvsmbr_partitions_type_object;

PyObject *pyvsmbr_partitions_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyvsmbr_partitions_init(
     pyvsmbr_partitions_t *sequence_object );

void pyvsmbr_partitions_free(
      pyvsmbr_partitions_t *sequence_object );

Py_ssize_t pyvsmbr_partitions_len(
            pyvsmbr_partitions_t *sequence_object );

PyObject *pyvsmbr_partitions_getitem(
           pyvsmbr_partitions_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyvsmbr_partitions_iter(
           pyvsmbr_partitions_t *sequence_object );

PyObject *pyvsmbr_partitions_iternext(
           pyvsmbr_partitions_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSMBR_PARTITIONS_H ) */

