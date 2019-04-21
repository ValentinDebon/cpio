/*
	cpio.c
	Copyright (c) 2019, Valentin Debon

	This file is part of the cpio repository
	subject the BSD 3-Clause License, see LICENSE
*/
#include "cpio.h"

int
cpio_big_endian_serialize_at(struct cpio_stat *cpiostatp,
	unsigned char byte, size_t position) {
	int valid = 0;

	switch(position) {
	case 0:
		if(byte != 0x71) {
			valid = -1;
		}
		break;
	case 1:
		if(byte != 0xC7) {
			valid = -1;
		}
		break;
	case 2:
		cpiostatp->cs_dev = byte << 8;
		break;
	case 3:
		cpiostatp->cs_dev |= byte;
		break;
	case 4:
		cpiostatp->cs_ino = byte << 8;
		break;
	case 5:
		cpiostatp->cs_ino |= byte;
		break;
	case 6:
		cpiostatp->cs_mode = byte << 8;
		break;
	case 7:
		cpiostatp->cs_mode |= byte;
		break;
	case 8:
		cpiostatp->cs_uid = byte << 8;
		break;
	case 9:
		cpiostatp->cs_uid |= byte;
		break;
	case 10:
		cpiostatp->cs_gid = byte << 8;
		break;
	case 11:
		cpiostatp->cs_gid |= byte;
		break;
	case 12:
		cpiostatp->cs_nlink = byte << 8;
		break;
	case 13:
		cpiostatp->cs_nlink |= byte;
		break;
	case 14:
		cpiostatp->cs_rdev = byte << 8;
		break;
	case 15:
		cpiostatp->cs_rdev |= byte;
		break;
	case 16:
		cpiostatp->cs_mtime = byte << 24;
		break;
	case 17:
		cpiostatp->cs_mtime |= byte << 16;
		break;
	case 18:
		cpiostatp->cs_mtime |= byte << 8;
		break;
	case 19:
		cpiostatp->cs_mtime |= byte;
		break;
	case 20:
		cpiostatp->cs_namesize = byte << 8;
		break;
	case 21:
		cpiostatp->cs_namesize |= byte;
		break;
	case 22:
		cpiostatp->cs_filesize = byte << 24;
		break;
	case 23:
		cpiostatp->cs_filesize |= byte << 16;
		break;
	case 24:
		cpiostatp->cs_filesize |= byte << 8;
		break;
	case 25:
		cpiostatp->cs_filesize |= byte;
		break;
	default:
		valid = -1;
		break;
	}

	return valid;
}

int
cpio_little_endian_serialize_at(struct cpio_stat *cpiostatp,
	unsigned char byte, size_t position) {
	int valid = 0;

	switch(position) {
	case 0:
		if(byte != 0xC7) {
			valid = -1;
		}
		break;
	case 1:
		if(byte != 0x71) {
			valid = -1;
		}
		break;
	case 2:
		cpiostatp->cs_dev = byte;
		break;
	case 3:
		cpiostatp->cs_dev |= byte << 8;
		break;
	case 4:
		cpiostatp->cs_ino = byte;
		break;
	case 5:
		cpiostatp->cs_ino |= byte << 8;
		break;
	case 6:
		cpiostatp->cs_mode = byte;
		break;
	case 7:
		cpiostatp->cs_mode |= byte << 8;
		break;
	case 8:
		cpiostatp->cs_uid = byte;
		break;
	case 9:
		cpiostatp->cs_uid |= byte << 8;
		break;
	case 10:
		cpiostatp->cs_gid = byte;
		break;
	case 11:
		cpiostatp->cs_gid |= byte << 8;
		break;
	case 12:
		cpiostatp->cs_nlink = byte;
		break;
	case 13:
		cpiostatp->cs_nlink |= byte << 8;
		break;
	case 14:
		cpiostatp->cs_rdev = byte;
		break;
	case 15:
		cpiostatp->cs_rdev |= byte << 8;
		break;
	case 16:
		cpiostatp->cs_mtime = byte;
		break;
	case 17:
		cpiostatp->cs_mtime |= byte << 8;
		break;
	case 18:
		cpiostatp->cs_mtime |= byte << 16;
		break;
	case 19:
		cpiostatp->cs_mtime |= byte << 24;
		break;
	case 20:
		cpiostatp->cs_namesize = byte;
		break;
	case 21:
		cpiostatp->cs_namesize |= byte << 8;
		break;
	case 22:
		cpiostatp->cs_filesize = byte;
		break;
	case 23:
		cpiostatp->cs_filesize |= byte << 8;
		break;
	case 24:
		cpiostatp->cs_filesize |= byte << 16;
		break;
	case 25:
		cpiostatp->cs_filesize |= byte << 24;
		break;
	default:
		valid = -1;
		break;
	}

	return valid;
}

int
cpio_odc_serialize_at(struct cpio_stat *cpiostatp,
	unsigned char byte, size_t position) {
	int valid;

	byte -= '0';
	if(byte <= 7) {
		valid = 0;

		switch(position) {
		case 0:
		case 2:
		case 4:
			if(byte != 0) {
				valid = -1;
			}
			break;
		case 1:
		case 3:
		case 5:
			if(byte != 7) {
				valid = -1;
			}
			break;
		case 6:
			cpiostatp->cs_dev = 0;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			cpiostatp->cs_dev = cpiostatp->cs_dev * 8 + byte;
			break;
		case 12:
			cpiostatp->cs_ino = 0;
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			cpiostatp->cs_ino = cpiostatp->cs_ino * 8 + byte;
			break;
		case 18:
			cpiostatp->cs_mode = 0;
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			cpiostatp->cs_mode = cpiostatp->cs_mode * 8 + byte;
			break;
		case 24:
			cpiostatp->cs_uid = 0;
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
			cpiostatp->cs_uid = cpiostatp->cs_uid * 8 + byte;
			break;
		case 30:
			cpiostatp->cs_gid = 0;
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
			cpiostatp->cs_gid = cpiostatp->cs_gid * 8 + byte;
			break;
		case 36:
			cpiostatp->cs_nlink = 0;
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
			cpiostatp->cs_nlink = cpiostatp->cs_nlink * 8 + byte;
			break;
		case 42:
			cpiostatp->cs_rdev = 0;
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
			cpiostatp->cs_rdev = cpiostatp->cs_rdev * 8 + byte;
			break;
		case 48:
			cpiostatp->cs_mtime = 0;
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
			cpiostatp->cs_mtime = cpiostatp->cs_mtime * 8 + byte;
			break;
		case 59:
			cpiostatp->cs_namesize = 0;
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
			cpiostatp->cs_namesize = cpiostatp->cs_namesize * 8 + byte;
			break;
		case 65:
			cpiostatp->cs_filesize = 0;
		case 66:
		case 67:
		case 68:
		case 69:
		case 70:
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
			cpiostatp->cs_filesize = cpiostatp->cs_filesize * 8 + byte;
			break;
		default:
			valid = -1;
			break;
		}
	} else {
		valid = -1;
	}

	return valid;
}

