#include <stdlib.h>
#include <string.h>

unsigned long char_to_hex(const char c)
{
	char str[] = { c , '\0' };
	return strtoul(str, NULL, 16);
}

void hexstr_to_hexarr(const char *hexstr, int *buf)
{
	for(int i = 0; i < strlen(hexstr); i++) {
		buf[i] = char_to_hex(hexstr[i]);
	}
}