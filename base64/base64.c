#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "base64.h"

typedef struct encoding_gadget {
	unsigned char octet0, octet1, octet2;
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

int gadget_arr_len(size_t hex_str_len)
{
	int ret_val = 0;

	if (hex_str_len <= 3) {
		ret_val = 1;
	}
	else {
		ret_val = (int)ceil(hex_str_len / 3);
	}

	return ret_val;
}

encoding_gadget *build_gadget_array(const char *hex_str, int hex_str_len, int gadget_array_len)
{
	encoding_gadget *gadgets = malloc(sizeof(encoding_gadget) * gadget_array_len);
	int idx = 0;
	int octet_index = 0;

	for (int i = 0; i < hex_str_len; i++) {
		if (octet_index == 0) {
			gadgets[idx].octet0 = hex_str[i];
			octet_index++;
		}
		else if (octet_index == 1) {
			gadgets[idx].octet1 = hex_str[i];
			octet_index++;
		}
		else {
			gadgets[idx].octet2 = hex_str[i];
			octet_index = 0;
			idx++;
		}
	}

	return gadgets;
}

const char *hex_to_base64(const char *hex_str) 
{
	const int hex_str_len = strlen(hex_str);
	const int gadget_array_len = gadget_arr_len(hex_str_len);
	encoding_gadget *gadgets = build_gadget_array(hex_str, hex_str_len, gadget_array_len);


	free(gadgets);
	return "blah";
}
