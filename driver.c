#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./base64/base64.h"

int main()
{
    char str_to_decode[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    (void)hex_to_base64(str_to_decode);
    printf("\n");

    return 0;
}