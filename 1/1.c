#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libcryptopals.h"

int main(int argc, char *argv[]) {
	char first[1024], second[1024];
	hex_decode(argv[1], first);
	base64_encode(first, strlen(argv[1]) / 2, second);
	printf("%s\n%s\n", first, second);
	return 0;
}