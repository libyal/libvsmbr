/*
 * Volume type functions
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

#include <common.h>
#include <types.h>

#include "libvsmbr_volume_type.h"

#if defined( HAVE_DEBUG_OUTPUT )

libvsmbr_volume_type_t libvsmbr_volume_types[ ] = {
	{ 0x00,		"Empty" },
	{ 0x01,		"FAT12 (CHS)" },
	{ 0x02,		"XENIX root" },
	{ 0x03,		"XENIX user" },
	{ 0x04,		"FAT16 < 32 MiB (CHS)" },
	{ 0x05,		"Extended (CHS)" },
	{ 0x06,		"FAT16 (CHS)" },
	{ 0x07,		"HPFS/NTFS" },
	{ 0x08,		"AIX" },
	{ 0x09,		"AIX bootable" },
	{ 0x0a,		"OS/2 Boot Manager" },
	{ 0x0b,		"FAT32 (CHS)" },
	{ 0x0c,		"FAT32 (LBA)" },
	{ 0x0e,		"FAT16 (LBA)" },
	{ 0x0f,		"Extended (LBA)" },
	{ 0x10,		"OPUS" },
	{ 0x11,		"Hidden FAT12 (CHS)" },
	{ 0x12,		"Compaq diagnostics" },
	{ 0x14,		"Hidden FAT16 < 32 MiB (CHS)" },
	{ 0x16,		"Hidden FAT16 (CHS)" },
	{ 0x17,		"Hidden HPFS/NTFS" },
	{ 0x18,		"AST SmartSleep" },
	{ 0x1b,		"Hidden FAT32 (CHS)" },
	{ 0x1c,		"Hidden FAT32 (LBA)" },
	{ 0x1e,		"Hidden FAT16 (LBA)" },
	{ 0x24,		"NEC DOS" },
	{ 0x39,		"Plan 9" },
	{ 0x3c,		"PartitionMagic recovery" },
	{ 0x40,		"Venix 80286" },
	{ 0x41,		"PPC PReP Boot" },
	{ 0x42,		"SFS / MS LDM" },
	{ 0x4d,		"QNX4.x" },
	{ 0x4e,		"QNX4.x 2nd part" },
	{ 0x4f,		"QNX4.x 3rd part" },
	{ 0x50,		"OnTrack DM" },
	{ 0x51,		"OnTrack DM6 Aux1" },
	{ 0x52,		"CP/M" },
	{ 0x53,		"OnTrack DM6 Aux3" },
	{ 0x54,		"OnTrackDM6" },
	{ 0x55,		"EZ-Drive" },
	{ 0x56,		"Golden Bow" },
	{ 0x5c,		"Priam Edisk" },
	{ 0x61,		"SpeedStor" },
	{ 0x63,		"GNU HURD or SysV" },
	{ 0x64,		"Novell Netware 286" },
	{ 0x65,		"Novell Netware 386" },
	{ 0x70,		"DiskSecure Multi-Boot" },
	{ 0x75,		"PC/IX" },
	{ 0x78,		"XOSL" },
	{ 0x80,		"Old Minix" },
	{ 0x81,		"Minix / old Linux" },
	{ 0x82,		"Linux swap / Solaris" },
	{ 0x83,		"Linux" },
	{ 0x84,		"OS/2 hidden C: drive" },
	{ 0x85,		"Linux extended" },
	{ 0x86,		"NTFS volume set" },
	{ 0x87,		"NTFS volume set" },
	{ 0x8e,		"Linux LVM" },
	{ 0x93,		"Amoeba" },
	{ 0x94,		"Amoeba BBT" },
	{ 0x9f,		"BSD/OS" },
	{ 0xa0,		"IBM Thinkpad hibernation" },
	{ 0xa5,		"FreeBSD" },
	{ 0xa6,		"OpenBSD" },
	{ 0xa7,		"NeXTSTEP" },
	{ 0xa9,		"NetBSD" },
	{ 0xaf,		"MacOS-X" },
	{ 0xb7,		"BSDI fs" },
	{ 0xb8,		"BSDI swap" },
	{ 0xbb,		"Boot Wizard hidden" },
	{ 0xc1,		"DRDOS/sec (FAT-12)" },
	{ 0xc4,		"DRDOS/sec (FAT-16 < 32 MiB)" },
	{ 0xc6,		"DRDOS/sec (FAT-16)" },
	{ 0xc7,		"Syrinx" },
	{ 0xda,		"Non-FS data" },
	{ 0xdb,		"CP/M / CTOS / ..." },
	{ 0xde,		"Dell Utility" },
	{ 0xdf,		"BootIt" },
	{ 0xe1,		"DOS access" },
	{ 0xe3,		"DOS R/O" },
	{ 0xe4,		"SpeedStor" },
	{ 0xeb,		"BeOS fs" },
	{ 0xee,		"EFI GPT protective" },
	{ 0xef,		"EFI System (FAT)" },
	{ 0xf0,		"Linux/PA-RISC boot" },
	{ 0xf1,		"SpeedStor" },
	{ 0xf4,		"SpeedStor" },
	{ 0xf2,		"DOS secondary" },
	{ 0xfd,		"Linux raid autodetect" },
	{ 0xfe,		"LANstep" },
	{ 0xff,		"BBT" },

	{ (uint16_t) -1, "Unknown" } };

/* Retrieves a string containing the value type description
 */
const char *libvsmbr_volume_type_get_description(
             uint8_t volume_type )
{
	int iterator = 0;

	while( ( libvsmbr_volume_types[ iterator ] ).volume_type != (uint16_t) -1 )
	{
		if( ( libvsmbr_volume_types[ iterator ] ).volume_type == (uint16_t) volume_type )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libvsmbr_volume_types[ iterator ] ).description );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

