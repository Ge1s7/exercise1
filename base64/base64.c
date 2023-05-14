#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"

// ancient programming meme: https://mathworld.wolfram.com/Crumb.html
typedef struct { unsigned char val : 2; } crumb;

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

unsigned long char_to_hex(const char c)
{
	char str[] = { c , '\0' };
	return strtoul(str, NULL, 16);
}

void hexstr_to_hexarr(const char *hexstr, int *buf)
{
	for(int i = 0; i < strlen(hexstr); i++) {
		buf[i] = char_to_hex(hexstr[i]);
	}
}

crumb pop_and_free(Queue *q)
{
	crumb *temp = pop(&(*q));
	crumb retval = { .val = temp->val };
	free(temp);
	return retval;
}

// This assumes a big-endian processor is executing this code.
void enqueue_bits(int *hexarr, size_t arr_size, Queue *q)
{
	const unsigned char mask = 0b11;
	const int shifts[] = {2, 0};

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < 2; j++) {
			crumb *_crumb = malloc(sizeof(crumb));
			_crumb->val = (hexarr[i] >> shifts[j]) & mask;
			push(q, &(*_crumb));
		}
	}
}

char extract_six(Queue *q)
{
	unsigned char index = 0;

	index |= pop_and_free(q).val;
	index <<= 2;
	index |= pop_and_free(q).val;
	index <<= 2;
	index |= pop_and_free(q).val;

	if(q->size >= 3) {
	}
	else {

	}

	return BASE64_ALPHABET[index];
}

void hex_to_base64(const char *hexstr, char *buffer, size_t buf_size)
{
	const size_t hexstr_length = strlen(hexstr);
	int hexarr[hexstr_length];
	Queue q = new_queue();

	hexstr_to_hexarr(hexstr, hexarr);
	enqueue_bits(hexarr, hexstr_length, &q);
	printf("%c\n", extract_six(&q));
}
