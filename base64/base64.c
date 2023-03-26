#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "base64.h"

typedef struct encoding_gadget {
	unsigned char octet1, octet2, octet3;
}encoding_gadget;

const char BASE64_ALPHABET[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

const char *hex_to_base64(const char *hex_str)
{
	printf("%s\n", hex_str);
	const int hex_str_len = strlen(hex_str);

	for (int i = 0; i < hex_str_len; i += 3) {
		if (hex_str_len < 3) {
			
		}

		encoding_gadget gadget = {
			hex_str[i],
			hex_str[i + 1],
			hex_str[i + 2]
		};
		printf("octet1: %c, octet2: %c, octet3: %c\n", gadget.octet1, gadget.octet2, gadget.octet3);
	}
	return NULL;
}