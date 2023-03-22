#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char BASE64_TABLE[64]; 

unsigned long char_to_hex(const char c)
{
    char str[] = { c , '\0' };
    return strtoul(str, NULL, 16);
}

void populate_table(int *index, const char begin, const char end)
{
    char curr_char = begin;
    for (; curr_char <= end; (*index)++) {
        BASE64_TABLE[(*index)] = curr_char++;
    }
}

unsigned char bot2(unsigned char halfword)
{
    return halfword & 0x03;
}

unsigned char mid2(unsigned char halfword)
{
    return halfword & 0x0c;
}

unsigned char top4(unsigned char halfword)
{
    return halfword & 0xf0;
}

void init_base64_table()
{
    int i = 0;

    populate_table(&i, 'A', 'Z');
    populate_table(&i, 'a', 'z');
    populate_table(&i, '0', '9');

    BASE64_TABLE[i++] = '+';
    BASE64_TABLE[i] = '/';
}

bool padding_required(size_t str_length)
{
    return (str_length * 8) % 6 != 0;
}

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
    
}

bool is_even (size_t len)
{
    return len % 2 == 0; 
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