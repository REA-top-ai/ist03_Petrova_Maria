#ifndef BITMAP_FILELOADER_H
#define BITMAP_FILELOADER_H

namespace Pictures {
    bool load_file_bytes(const char* path, unsigned char* headers, const int size);
}

#endif
