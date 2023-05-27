#include <stdlib.h>
#include <string.h>

unsigned long char_to_hex(const char c)
{
	char str[] = { c , '\0' };
	return strtoul(str, NULL, 16);
}

char hex_to_char(int num)
{
	char retval;
	switch(num){
		case 0x0:
		case 0x1:
		case 0x2:
		case 0x3:
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
		case 0x8:
		case 0x9:
			retval =  num + '0';
			break;
		case 0xa:
			retval = 'a';
			break;
		case 0xb:
			retval = 'b';
			break;
		case 0xc:
			retval = 'c';
			break;
		case 0xd:
			retval = 'd';
			break;
		case 0xe:
			retval = 'e';
			break;
		case 0xf:
			retval = 'f';
			break;
		default:
			break;
	}
	return retval;
}

void hexstr_to_hexarr(const char *hexstr, int *buf)
{
	for(int i = 0; i < strlen(hexstr); i++) {
		buf[i] = char_to_hex(hexstr[i]);
	}
}