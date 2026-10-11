#ifndef BITMAP_BYTES_H
#define BITMAP_BYTES_H

namespace Pictures {
    unsigned int binomial(const int n, const int k);
    unsigned int power_of_256(const int degree);
    unsigned int combine_bytes(const unsigned char* bytes, const int count);
    int select_4_bites(const unsigned char* bytes);
    short select_2_bites(const unsigned char* bytes);
}

#endif
