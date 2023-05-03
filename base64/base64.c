#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "queue.h"

typedef struct { unsigned char data : 2; } bitfield_width2;

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

// not thread safe
void enqueue_bits(const char *hex_str, Queue *q)
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

void print_bits(Queue q)
{
	while (q.size != 0) {
		printf("%#x ", ((bitfield_width2*) pop(&q))->data);
	}
	puts("");
}

void perror_and_gtfo(size_t base64_strlen, size_t buffer_size)
{
	char fmt[] = "Buffer size not large enough for conversion. Required length: %d. Given length: %d.\n";
	char err_msg[255];
	sprintf(err_msg, fmt, base64_strlen, buffer_size);
	errno = EINVAL;
	perror(err_msg);
	exit(errno);
}

void hex_to_base64(const char *hex_str, char *buffer, size_t buffer_size) 
{
	const size_t base64_strlen = ceil(strlen(hex_str) * 1.5);

	if (buffer_size < base64_strlen) {
		perror_and_gtfo(base64_strlen, buffer_size);
	}

	Queue q;
	queue_init(&q);
	enqueue_bits(hex_str, &q);
}
