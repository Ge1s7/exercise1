#include <stdlib.h>
#include <ctype.h>
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
			retval = '0';
			break;
		case 0x1:
			retval = '1';
			break;
		case 0x2:
			retval = '2';
			break;
		case 0x3:
			retval = '3';
			break;
		case 0x4:
			retval = '4';
			break;
		case 0x5:
			retval = '5';
			break;
		case 0x6:
			retval = '6';
			break;
		case 0x7:
			retval = '7';
			break;
		case 0x8:
			retval = '8';
			break;
		case 0x9:
			retval = '9';
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