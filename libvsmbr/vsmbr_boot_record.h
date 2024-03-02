/*
 * Master Boot Record (MBR) boot record definitions
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

#if !defined( _VSMBR_BOOT_RECORD_H )
#define _VSMBR_BOOT_RECORD_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vsmbr_boot_record_classical vsmbr_boot_record_classical_t;

struct vsmbr_boot_record_classical
{
	/* Boot loader
	 * Consists of 446 bytes
	 */
	uint8_t boot_loader[ 446 ];

	/* Partition table
	 * Consist of 64 bytes
	 * Contains 4 x 16-byte partition entries
	 */
	uint8_t partition_entries[ 64 ];

	/* The boot signature
	 * Consists of 2 bytes
	 * Contains 0x55 0xaa
	 */
	uint8_t boot_signature[ 2 ];
};

typedef struct vsmbr_boot_record_modern vsmbr_boot_record_modern_t;

struct vsmbr_boot_record_modern
{
	/* Boot loader
	 * Consists of 440 bytes
	 */
	uint8_t boot_loader[ 440 ];

	/* Disk identity
	 * Consists of 4 bytes
	 */
	uint8_t disk_identity[ 4 ];

	/* Padding
	 * Consists of 2 bytes
	 * Contains 0x00
	 */
	uint8_t padding[ 2 ];

	/* Partition table
	 * Consist of 64 bytes
	 * Contains 4 x 16-byte partition entries
	 */
	uint8_t partition_entries[ 64 ];

	/* The boot signature
	 * Consists of 2 bytes
	 * Contains 0x55 0xaa
	 */
	uint8_t boot_signature[ 2 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSMBR_BOOT_RECORD_H ) */

