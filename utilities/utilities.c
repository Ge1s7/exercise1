#include "utilities.h"

unsigned long char_to_hex(const char c)
{
    char str[] = { c , '\0' };
    return strtoul(str, NULL, 16);
}

bool is_even (size_t len)
{
    return len % 2 == 0; 
}

bool padding_required(size_t str_length)
{
    return (str_length * 8) % 6 != 0;
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
