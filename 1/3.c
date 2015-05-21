#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../libcryptopals.h"

double g_freq_table[256];

void init_freq_table(void) {
	unsigned char buf[4096];
	FILE *fin = fopen("../data/english_text.txt", "r");
	unsigned cnt = 0;
	ssize_t read;
	while ((read = fread(buf, 1, sizeof(buf), fin)) > 0) {
		for (size_t i = 0; i < read; ++i) {
			++cnt;
			++g_freq_table[buf[i]];
		}
	}
	for (int i = 0; i < 256; ++i) {
		g_freq_table[i] /= cnt;
	}
}

double calc_diff(char *msg, size_t n) {
	unsigned char *umsg = (unsigned char*)msg;
	double freq_tmp[256] = { 0 };
	unsigned cnt = 0;
	for (size_t i = 0; i < n; ++i) {
		++freq_tmp[umsg[i]];
		++cnt;
	}
	for (int i = 0; i < 256; ++i)
		freq_tmp[i] /= cnt;
	double diff = 0;
	for (size_t i = 0; i < 256; ++i)
		diff += pow(freq_tmp[i] - g_freq_table[i], 2);
	return diff;
}

void encrypt_single_xor(char *in, char key, size_t n, char *out) {
	for (size_t i = 0; i < n; ++i)
		out[i] = in[i] ^ key;
}

int main(int argc, char *argv[]) {
	char encrypted[4096], work[4096];
	unsigned len = strlen(argv[1]) / 2;
	hex_decode(argv[1], encrypted);
	init_freq_table();
	double best_diff = 1e6;
	int best_key = 0;
	for (int key = 0; key < 256; ++key) {
		encrypt_single_xor(encrypted, key, len, work);
		double diff = calc_diff(work, len);
		if (diff < best_diff) {
			best_diff = diff;
			best_key = key;
		}
	}
	encrypt_single_xor(encrypted, best_key, len, work);
	printf("diff=%lf key=%d\n%s\n", best_diff, best_key, work);
	return 0;
}