/*
 * Cylinder Head Sector (CHS) address functions
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

#if !defined( _LIBVSMBR_CHS_ADDRESS_H )
#define _LIBVSMBR_CHS_ADDRESS_H

#include <common.h>
#include <types.h>

#include "libvsmbr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsmbr_chs_address libvsmbr_chs_address_t;

struct libvsmbr_chs_address
{
	/* The cylinder
	 */
	uint16_t cylinder;

	/* The head
	 */
	uint8_t head;

	/* The sector
	 */
	uint8_t sector;
};

int libvsmbr_chs_address_initialize(
     libvsmbr_chs_address_t **chs_address,
     libcerror_error_t **error );

int libvsmbr_chs_address_free(
     libvsmbr_chs_address_t **chs_address,
     libcerror_error_t **error );

int libvsmbr_chs_address_copy_from_byte_stream(
     libvsmbr_chs_address_t *chs_address,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSMBR_CHS_ADDRESS_H ) */

