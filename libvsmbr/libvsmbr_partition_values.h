/*
 * The partition values functions
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

#if !defined( _LIBVSMBR_PARTITION_VALUES_H )
#define _LIBVSMBR_PARTITION_VALUES_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_partition_values libvsmbr_partition_values_t;

struct libvsmbr_partition_values
{
	/* The type
	 */
	uint8_t type;

	/* The offset of the corresponding partition record
	 */
	off64_t partition_record_offset;

	/* The sector number
	 */
	uint32_t sector_number;

	/* The number of sectors
	 */
	uint32_t number_of_sectors;
};

int libvsmbr_partition_values_initialize(
     libvsmbr_partition_values_t **partition_values,
     libcerror_error_t **error );

int libvsmbr_partition_values_free(
     libvsmbr_partition_values_t **partition_values,
     libcerror_error_t **error );

int libvsmbr_partition_values_get_type(
     libvsmbr_partition_values_t *partition_values,
     uint8_t *type,
     libcerror_error_t **error );

int libvsmbr_partition_values_get_sector_number(
     libvsmbr_partition_values_t *partition_values,
     uint32_t *sector_number,
     libcerror_error_t **error );

int libvsmbr_partition_values_get_number_of_sectors(
     libvsmbr_partition_values_t *partition_values,
     uint32_t *number_of_sectors,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_PARTITION_VALUES_H ) */

