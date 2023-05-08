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

unsigned long ascii_to_hex(const char c)
{
	char str[] = { c , '\0' };
	return strtoul(str, NULL, 16);
}

bitfield_width2 pop_and_free(Queue *q)
{
	bitfield_width2 *temp = pop(&(*q));
	bitfield_width2 bitfield = {.data = temp->data};
	free(temp);
	return bitfield;
}

// This assumes a big-endian processor is executing this code.
// TODO: Make this code architecure agnostic.
void enqueue_bits(const char *hex_str, Queue *q)
{
	for(int i = 0; i < strlen(hex_str); i++) {
		bitfield_width2 *upper_two = malloc(sizeof(bitfield_width2));
		bitfield_width2 *himid_two = malloc(sizeof(bitfield_width2));
		bitfield_width2 *lomid_two = malloc(sizeof(bitfield_width2));
		bitfield_width2 *lower_two = malloc(sizeof(bitfield_width2));

		upper_two->data = (hex_str[i] & 0b11000000) >> 6;
		himid_two->data = (hex_str[i] & 0b00110000) >> 4;
		lomid_two->data = (hex_str[i] & 0b00001100) >> 2;
		lower_two->data = hex_str[i] & 0b00000011;

		push(q, &(*upper_two));
		push(q, &(*himid_two));
		push(q, &(*lomid_two));
		push(q, &(*lower_two));
	}
}

// void print_bits(Queue q)
// {
// 	while(q.size != 0) {
// 		printf("%#x ", pop_and_free(q).data);
// 	}
// 	puts("");
// }

char extract_six(Queue *q)
{
	unsigned char index = 0;

	index |= pop_and_free(q).data;
	index <<= 2;
	index |= pop_and_free(q).data;
	index <<= 2;
	index |= pop_and_free(q).data;

	return BASE64_ALPHABET[index];
}

void perror_and_gtfo(size_t base64str_len, size_t buffer_size)
{
	char fmt[] = "Buffer size not large enough for conversion. Required length: %d. Given length: %d.\n";
	char err_msg[128];
	sprintf(err_msg, fmt, base64str_len, buffer_size);
	errno = EINVAL;
	perror(err_msg);
	exit(errno);
}

void hex_to_base64(const char *hex_str, char *buffer, size_t buffer_size) 
{
	//printf("string val == %s\n", hex_str);
	const size_t base64_strlen = ceil(strlen(hex_str) * 1.5);
	if(buffer_size < base64_strlen) {
		perror_and_gtfo(base64_strlen, buffer_size);
	}

	Queue q;
	queue_init(&q);
	enqueue_bits(hex_str, &q);


	printf("%c", extract_six(&q));
	puts("");
}
