#include <string.h>
#include <assert.h>
#include "crypto/set1.h"

const size_t BUFFER_SIZE = 255;

void base64()
{
	const char test_str_1[] = "4d";
	const char test_str_2[] = "4d61";
	const char test_str_3[] = "4d616e";
	const char test_str_4[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	char result1[BUFFER_SIZE];
	hex_to_base64(test_str_1, result1, sizeof(result1));
	assert(strcmp("TQ", result1) == 0);

	char result2[BUFFER_SIZE];
	hex_to_base64(test_str_2, result2, sizeof(result2));
	assert(strcmp("TWE", result2) == 0);

	char result3[BUFFER_SIZE];
	hex_to_base64(test_str_3, result3, sizeof(result3));
	assert(strcmp("TWFu", result3) == 0);

	char result4[BUFFER_SIZE];
	hex_to_base64(test_str_4, result4, sizeof(result4));
	assert(strcmp("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t", result4) == 0);
}

void fixed_xor()
{
	const char str1[] = "1c0111001f010100061a024b53535009181c";
	const char str2[] = "686974207468652062756c6c277320657965";
	const char expected_result[] = "746865206b696420646f6e277420706c6179";
	char result[strlen(str1)];

	strxor(str1, str2, result);
	assert(strcmp(expected_result, result) == 0);
}

void decrypt_xored_string()
{
	char result[255];
	decode_xor_cipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", result);
	assert(strcmp(result, "Cooking MC's like a pound of bacon") == 0);
}

int main()
{
	base64();
	fixed_xor();
	decrypt_xored_string();

	return 0;
}
