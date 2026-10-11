#ifndef BITMAP_BMPREADER_H
#define BITMAP_BMPREADER_H

#include "BmpView.h"
#include "Pixel.h"

namespace Pictures {
    void read(const BmpView& bmp, const int x, const int y, Pixel& out);
    void print_corner(const BmpView& bmp, const char* name, const int x, const int y);
}

#endif
