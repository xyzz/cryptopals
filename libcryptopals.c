#include <stdlib.h>
#include <string.h>

const char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(char *buf, size_t n, char *out) {
	unsigned char *ubuf = (unsigned char*)buf;
	size_t i = 0;
	while (i < n) {
		unsigned m;
		if (i == n - 2) {
			m = ubuf[i + 1] * 256 + ubuf[i] * 256 * 256;
			*out++ = base64_table[(m >> 18) & 0x3f];
			*out++ = base64_table[(m >> 12) & 0x3f];
			*out++ = base64_table[(m >> 6) & 0x3f];
			*out++ = '=';
		} else if (i == n - 1) {
			m = ubuf[i] * 256 * 256;
			*out++ = base64_table[(m >> 18) & 0x3f];
			*out++ = base64_table[(m >> 12) & 0x3f];
			*out++ = '=';
			*out++ = '=';
		} else {
			m = ubuf[i + 2] + ubuf[i + 1] * 256 + ubuf[i] * 256 * 256;
			*out++ = base64_table[(m >> 18) & 0x3f];
			*out++ = base64_table[(m >> 12) & 0x3f];
			*out++ = base64_table[(m >> 6) & 0x3f];
			*out++ = base64_table[(m >> 0) & 0x3f];
		}
		i += 3;
	}
	*out = '\0';
}

void hex_decode(char *buf, char *out) {
	char tmp[3] = { 0 };
	char *c = buf;
	char *o = out;
	while (*c) {
		tmp[0] = c[0];
		tmp[1] = c[1];
		*o++ = strtoul(tmp, NULL, 16);
		c += 2;
	}
	*o = '\0';
}

const char *hex_table = "0123456789abcdefgh";
void hex_encode(char *buf, size_t n, char *out) {
	for (size_t i = 0; i < n; ++i) {
		unsigned c = buf[i];
		*out++ = hex_table[c >> 4];
		*out++ = hex_table[c & 0xF];
	}
	*out++ = '\0';
}

void xor_bufs(char *first, char *second, size_t n, char *output) {
	for (size_t i = 0; i < n; ++i)
		output[i] = first[i] ^ second[i];
}