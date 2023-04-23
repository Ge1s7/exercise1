#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"

typedef struct bitfield_width2{
	unsigned char data : 2;
} bitfield_width2;

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

void iterate(const char *hex_str, Queue *q)
{
		unsigned char lo2 = 0x03;
		for(int i = 0; i < strlen(hex_str); i++) {
			static bitfield_width2 upper_two, himid_two, lomid_two, lower_two;

			for (int j = 0 ; j < 4; j++) {
				switch(j) {
					case 0:
						upper_two.data = hex_str[i] >> 6;
						push(q, &upper_two);
						break;
					case 1:
						himid_two.data = (hex_str[i] >> 4) & lo2;
						push(q, &himid_two);
						break;
					case 2:
						lomid_two.data = (hex_str[i] >> 2) & lo2;
						push(q, &lomid_two);
						break;
					case 3:
						lower_two.data = hex_str[i] & lo2;
						push(q, &lower_two);
						break;
					default: break;
				}
			}
		}
}

const char *hex_to_base64(const char *hex_str) 
{
	Queue q;
	queue_init(&q);
	iterate(hex_str, &q);

	printf("%#x ", ((bitfield_width2*) pop(&q))->data);
	printf("%#x ", ((bitfield_width2*) pop(&q))->data);
	printf("%#x ", ((bitfield_width2*) pop(&q))->data);
	printf("%#x\n", ((bitfield_width2*) pop(&q))->data);
	return "blah";
}
