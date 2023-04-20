#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "queue.h"

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
	int idx = 0;
	int octet_index = 0;
	const int hex_str_len = strlen(hex_str);

	Queue q;
	queue_init(&q);

	
	return "blah";
}
