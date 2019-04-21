#ifndef CPIO_H
#define CPIO_H

#include <sys/types.h>

#define CPIO_HEADER_SIZE 26
#define CPIO_ODC_HEADER_SIZE 76

struct cpio_stat {
	dev_t cs_dev;
	ino_t cs_ino;
	mode_t cs_mode;
	uid_t cs_uid;
	gid_t cs_gid;
	nlink_t cs_nlink;
	dev_t cs_rdev;
	time_t cs_mtime;
	size_t cs_namesize;
	off_t cs_filesize;
};

int
cpio_big_endian_serialize_at(struct cpio_stat *cpiostatp,
	unsigned char byte, size_t position);

int
cpio_little_endian_serialize_at(struct cpio_stat *cpiostatp,
	unsigned char byte, size_t position);

int
cpio_odc_serialize_at(struct cpio_stat *cpiostatp,
	unsigned char byte, size_t position);

/* CPIO_H */
#endif
