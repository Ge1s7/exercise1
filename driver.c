#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "./base64/base64.h"

int main()
{
    char test_str_1[] = "Man";
    char test_str_2[] = "Ma";
    char test_str_3[] = "M";
    char test_str_4[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    const char *result1 = hex_to_base64(test_str_1);
    assert(strcmp("TWFu", result1) == 0);

    const char *result2 = hex_to_base64(test_str_2);
    assert(strcmp("TWE", result2) == 0);

    const char *result3 = hex_to_base64(test_str_3);
    assert(strcmp("TQ", result3) == 0);

    const char *result4 = hex_to_base64(test_str_4);
    assert(strcmp("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t", result4) == 0);

    return 0;
}