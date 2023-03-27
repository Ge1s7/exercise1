#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

typedef struct encoding_gadget {
	unsigned char octet0, octet1, octet2;
} encoding_gadget;

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
	return hex_str_len <= 3
		? 1
		: (int)ceil(hex_str_len / 3);
}

encoding_gadget *build_gadget_array(const char *hex_str, int hex_str_len, int gadget_array_len)
{
	int idx = 0;
	int octet_index = 0;
	encoding_gadget *gadgets = malloc(sizeof(encoding_gadget) * gadget_array_len);

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


unsigned char sextet0(unsigned char octet0)
{
	printf("%#hx\n",octet0);
	printf("%c\n",BASE64_ALPHABET[octet0 >> 2]);
	return octet0 >> 2;
}

unsigned char sextet1(unsigned char octet0, unsigned char octet1)
{
	unsigned char oct0_bot2 = octet0 & 0x03;
	unsigned char oct1_top4 = octet1 & 0xf0;
	unsigned char ret_val = 0;

	ret_val |= (oct0_bot2 << 4);
	ret_val |= (oct1_top4 >> 4);

	return ret_val;
}

unsigned char sextet2(unsigned char octet1, unsigned char octet2)
{
	unsigned char oct1_bot4;
	unsigned char oct2_top2;
	return '0';
}

unsigned char sextet3(unsigned char octet2)
{
	return octet2 & 0x3f;
}

const char *hex_to_base64(const char *hex_str) 
{
	int idx = 0;
	int octet_index = 0;
	const int hex_str_len = strlen(hex_str);
	const int gadget_array_len = gadget_arr_len(hex_str_len);
	encoding_gadget *gadgets = build_gadget_array(hex_str, hex_str_len, gadget_array_len);

	sextet0(gadgets[0].octet0);


	free(gadgets);
	return "blah";
}
