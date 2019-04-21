/*
	main.c
	Copyright (c) 2019, Valentin Debon

	This file is part of the cpio repository
	subject the BSD 3-Clause License, see LICENSE
*/
#include "cpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int
main(int argc,
	char **argv) {
	char *buffer = malloc(CPIO_ODC_HEADER_SIZE);

	while(true) {
		struct cpio_stat cpiostat;
		size_t headerposition = 0;

		if(read(0, buffer, CPIO_ODC_HEADER_SIZE) != CPIO_ODC_HEADER_SIZE) {
			break;
		}

		while(headerposition != CPIO_ODC_HEADER_SIZE
			&& cpio_odc_serialize_at(&cpiostat, buffer[headerposition], headerposition) == 0) {
			headerposition++;
		}
		printf("dev: %d\nino: %llu\nmode: %ho\nuid: %u\ngid: %u\nnlink: %hu\nrdev: %d\nmtime: %snamesize: %ld\nfilesize: %lld\n",
			cpiostat.cs_dev, cpiostat.cs_ino, cpiostat.cs_mode,
			cpiostat.cs_uid, cpiostat.cs_gid, cpiostat.cs_nlink,
			cpiostat.cs_rdev, ctime(&cpiostat.cs_mtime), cpiostat.cs_namesize,
			cpiostat.cs_filesize);

		buffer = realloc(buffer, cpiostat.cs_namesize);
		read(0, buffer, cpiostat.cs_namesize);
		puts(buffer);
		if(strcmp("TRAILER!!!", buffer) == 0) {
			break;
		}

		buffer = realloc(buffer, cpiostat.cs_filesize);
		read(0, buffer, cpiostat.cs_filesize);
		fflush(stdout);
		write(1, buffer, cpiostat.cs_filesize);

	}

	free(buffer);

	return 0;
}
