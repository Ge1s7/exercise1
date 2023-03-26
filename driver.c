#include <stdio.h>
#include <string.h>
#include "./utilities/utilities.h"

const char BASE64_TABLE[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

char *decode_hexstring(const char *str)
{
    size_t base16_strlen = strlen(str);
    int num_bit_sextets = (base16_strlen * 8 ) / 6;
    const int base64_strlen = !padding_required(base16_strlen) ? num_bit_sextets + 1 : num_bit_sextets + 2; // yay null terminated strings
    char *decoded_string = malloc(sizeof(char) * base64_strlen);

    memset(decoded_string, 0, base64_strlen * 8);

    for (int i = 0; i < base64_strlen; i++)
    {
        // TODO: The thing.
    }
    return NULL;
}

int main()
{
    init_base64_table();
    char str_to_decode[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    size_t hex_str_len = strlen(str_to_decode);
    bool hex_str_even = is_even(hex_str_len);
    char new_char, halfword;
    halfword = new_char = 0;

    char nibbles[hex_str_len];
    memset(nibbles, 0, hex_str_len);

    for(int i = 0; i < hex_str_len; i++)
    {
        nibbles[i] = char_to_hex(str_to_decode[i]);
        printf("%#hx", nibbles[i]);
    }

    printf("\n");

    return 0;
}