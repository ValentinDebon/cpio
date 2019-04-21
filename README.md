# CPIO Serializer

CPIO headers serializer, working for binary CPIO format (little endian and big endian separated, not yet tested). And _odc_ CPIO, tested.

## Build

	clang -c -ansi -pedantic -Wall src/cpio.c

	clang -Isrc -o cpio-odc-test -ansi -pedantic -Wall src/cpio.c test/main.c

