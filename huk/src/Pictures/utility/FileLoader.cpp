#include "Pictures/utility/FileLoader.h"
#include <fstream>

namespace Pictures::utility {
    bool load_file_bytes(const char* path, unsigned char* headers, const int size) {
        std::ifstream file(path, std::ios::binary);
        if (!file) { return false; }
        file.read(reinterpret_cast<char*>(headers), size);
        return true;
    }
}
