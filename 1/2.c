#include <string.h>
#include <stdio.h>

#include "../libcryptopals.h"

int main(int argc, char *argv[]) {
	char buf1[1024], buf2[1024], output[1024];
	size_t len = strlen(argv[1]) / 2;
	hex_decode(argv[1], buf1);
	hex_decode(argv[2], buf2);
	xor_bufs(buf1, buf2, len, output);
	hex_encode(output, len, buf1);
	printf("%s\n", buf1);
	return 0;
}