#pragma once

void base64_encode(char *buf, size_t n, char *out);
void hex_decode(char *buf, char *out);
void hex_encode(char *buf, size_t n, char *out);
void xor_bufs(char *first, char *second, size_t n, char *output);
