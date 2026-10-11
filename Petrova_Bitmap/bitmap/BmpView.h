#ifndef BITMAP_BMPVIEW_H
#define BITMAP_BMPVIEW_H

namespace Pictures {
struct BmpView {
    const unsigned char* data;
    int size;
    int data_offset;
    int info_header_size;
    int width;
    int rows;
    bool bottom_up;
    int bpp;
};
}

#endif
