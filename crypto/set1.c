#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#include "utils.h"

// Ancient programming meme: https://mathworld.wolfram.com/Crumb.html
typedef struct { unsigned char val : 2; } Crumb;
typedef struct { char *str; int freq_score; } Guess;

void strxor(const char *src1, const char *src2, char *dst);

static Crumb pop_and_free(Queue *q)
{
	Crumb *temp = pop(&(*q));
	Crumb retval = { .val = temp->val };
	free(temp);
	return retval;
}

static void enqueue_crumbs(int *hexarr, size_t arr_size, Queue *q)
{
	const unsigned char mask = 0b11;
	const int shifts[] = {2, 0};

	for(int i = 0; i < arr_size; i++) {
		for (int j = 0; j < 2; j++) {
			Crumb *_crumb = malloc(sizeof(Crumb));
			_crumb->val = (hexarr[i] >> shifts[j]) & mask;
			push(q, &(*_crumb));
		}
	}
}

static char crumbs_to_base64(Queue *q)
{
	const char BASE64_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char index = 0;
	const int n = q->size >= 3 ? 3 : q->size;
	const int shifts[] = {4,2,0};

	for(int i = 0; i < n; i++) {
		index |= pop_and_free(q).val << shifts[i];
	}
	return BASE64_ALPHABET[index];
}

int calculate_freq_score(const char *str)
{
	const char common_letters[] = "etaoinshrdlu";
	int score = 0;
	for(int i = 0; i < strlen(str); i++) {
		if(strchr(common_letters, str[i]) != NULL)
			score++;
	}
	return score;
}

static void build_cipher_str(char *cipher_str, size_t src_len, char letter)
{
		unsigned char upper_half = (letter >> 4) & 0xf;
		unsigned char lower_half = letter & 0xf;

		int i;
		for(i = 0; i < src_len; i++) {
			if(i % 2 == 0)
				cipher_str[i] = hex_to_char(upper_half);
			else
				cipher_str[i] = hex_to_char(lower_half);
		}
		cipher_str[i] = '\0';
}

static char get_key(const char *hexstr, const size_t src_len)
{
	const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	Guess guesses[strlen(alphabet)];

	for(int i = 0; i < strlen(alphabet); i++) {
		char cipher[src_len];
		char decoded_hexarr[src_len];
		char ascii_str[src_len];

		build_cipher_str(cipher, src_len, alphabet[i]);
		strxor(hexstr, cipher, decoded_hexarr);
		hexstr_to_ascii(decoded_hexarr, ascii_str);
		guesses[i].str = malloc((sizeof(char) * strlen(ascii_str)) + 1);
		strcpy(guesses[i].str, ascii_str);
		guesses[i].freq_score = calculate_freq_score(ascii_str);
	}

	for(int i = 0; i < strlen(alphabet); i++) {
		printf("%s\n", guesses[i].str);
	}

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

	if(hexstr_length) {
		int hexarr1[hexstr_length], hexarr2[hexstr_length];
		hexstr_to_hexarr(src1, hexarr1);
		hexstr_to_hexarr(src2, hexarr2);

		int i;
		for(i = 0; i < hexstr_length; i++) {
			dst[i] = hex_to_char(hexarr1[i] ^ hexarr2[i]);
		}
		dst[i] = '\0';
	}
}

void decode_xor_cipher(const char *src, char *result)
{
	const size_t src_len = strlen(src);
	char key = get_key(src, src_len);

	char cipher[src_len];
	char decoded_hexarr[src_len];
	char ascii_str[src_len];

	build_cipher_str(cipher, src_len, key);
	strxor(src, cipher, decoded_hexarr);
	hexstr_to_ascii(decoded_hexarr, ascii_str);

	printf("%s\n", ascii_str);
}