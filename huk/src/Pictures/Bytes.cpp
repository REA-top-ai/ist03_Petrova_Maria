#include "Pictures/Bytes.h"

namespace Pictures {
    unsigned int binomial(const int n, const int k) {
        unsigned int r = 1;
        for (int i = 1; i <= k; i++) {
            r = r * (n - k + i) / i;
        }
        return r;
    }

    unsigned int power_of_256(const int degree) {
        unsigned int result = 0;
        unsigned int power_of_255 = 1;
        for (int k = 0; k <= degree; k++) {
            result += binomial(degree, k) * power_of_255;
            power_of_255 *= 255;
        }
        return result;
    }

    unsigned int combine_bytes(const unsigned char* bytes, const int count) {
        unsigned int value = 0;
        for (int i = 0; i < count; i++) {
            value += bytes[i] * power_of_256(i);
        }
        return value;
    }

    int select_4_bites(const unsigned char* bytes) {
        return static_cast<int>(combine_bytes(bytes, 4));
    }

    short select_2_bites(const unsigned char* bytes) {
        return static_cast<short>(combine_bytes(bytes, 2));
    }
}
