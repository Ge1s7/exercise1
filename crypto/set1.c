#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "utils.h"

// Ancient programming meme: https://mathworld.wolfram.com/Crumb.html
typedef struct { unsigned char val : 2; } crumb;

static crumb pop_and_free(Queue *q)
{
	crumb *temp = pop(&(*q));
	crumb retval = { .val = temp->val };
	free(temp);
	return retval;
}

static void enqueue_crumbs(int *hexarr, size_t arr_size, Queue *q)
{
	const unsigned char mask = 0b11;
	const int shifts[] = {2, 0};

	for(int i = 0; i < arr_size; i++) {
		for (int j = 0; j < 2; j++) {
			crumb *_crumb = malloc(sizeof(crumb));
			_crumb->val = (hexarr[i] >> shifts[j]) & mask;
			push(q, &(*_crumb));
		}
	}
}

// This assumes a big-endian processor is executing this code.
static char crumbs_to_base64(Queue *q)
{
	static const char BASE64_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char index = 0;
	const int n = q->size >= 3 ? 3 : q->size;
	const int shifts[] = {4,2,0};

	for(int i = 0; i < n; i++) {
		index |= pop_and_free(q).val << shifts[i];
	}
	return BASE64_ALPHABET[index];
}

void hex_to_base64(const char *src, char *dst, size_t len)
{
	const size_t hexstr_length = strlen(src);
	int hexarr[hexstr_length];
	Queue q = new_queue();

	hexstr_to_hexarr(src, hexarr);
	enqueue_crumbs(hexarr, hexstr_length, &q);
	memset(dst, 0, len);

	for(int i = 0; q.size != 0; i++)
		dst[i] = crumbs_to_base64(&q);
}

void strxor(const char *src1, const char *src2, char *dst)
{
	size_t hexstr_length = strlen(src1) == strlen(src2) ? strlen(src1) : 0;

	int hexarr1[hexstr_length], hexarr2[hexstr_length];

	if(hexstr_length) {
		hexstr_to_hexarr(src1, hexarr1);
		hexstr_to_hexarr(src2, hexarr2);

		int i;
		for(i = 0; i < hexstr_length; i++) {
			dst[i] = hex_to_char(hexarr1[i] ^ hexarr2[i]);
		}
		dst[i] = '\0';
	}
}