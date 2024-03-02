/*
 * The partition entry functions
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

#if !defined( _LIBVSMBR_PARTITION_ENTRY_H )
#define _LIBVSMBR_PARTITION_ENTRY_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_partition_entry libvsmbr_partition_entry_t;

struct libvsmbr_partition_entry
{
	/* The index
	 */
	uint8_t index;

	/* The flags
	 */
	uint8_t flags;

	/* The type
	 */
	uint8_t type;

	/* The start address in LBA
	 */
	uint32_t start_address_lba;

	/* The number of sectors
	 */
	uint32_t number_of_sectors;
};

int libvsmbr_partition_entry_initialize(
     libvsmbr_partition_entry_t **partition_entry,
     libcerror_error_t **error );

int libvsmbr_partition_entry_free(
     libvsmbr_partition_entry_t **partition_entry,
     libcerror_error_t **error );

int libvsmbr_partition_entry_read_data(
     libvsmbr_partition_entry_t *partition_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_PARTITION_ENTRY_H ) */

