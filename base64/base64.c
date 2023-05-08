#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "queue.h"

typedef struct { unsigned char data : 2; } bitfield_width2;
typedef struct { unsigned char upper_half : 4, lower_half : 4; } split_char;

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

bitfield_width2 pop_and_free(Queue *q)
{
	bitfield_width2 *temp = pop(&(*q));
	bitfield_width2 bitfield = {.data = temp->data};
	free(temp);
	return bitfield;
}

// This assumes a big-endian processor is executing this code.
// TODO: Make this code architecture agnostic.
void enqueue_bits(const char *hex_str, Queue *q)
{
    const unsigned char mask = 0b11;
    const int shifts[] = {6, 4, 2, 0};

    for (int i = 0; i < strlen(hex_str); i++) {
        for (int j = 0; j < 4; j++) {
            bitfield_width2 *bitfield = malloc(sizeof(bitfield_width2));
            bitfield->data = (hex_str[i] >> shifts[j]) & mask;
            push(q, &(*bitfield));
        }
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
