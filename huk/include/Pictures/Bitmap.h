#ifndef BITMAP_BITMAP_H
#define BITMAP_BITMAP_H

#include "Pictures/Pixel.h"

namespace Pictures {
    class Bitmap{
    public:
        void SetSize(int w, int h);
        Pixel GetPixel(int x, int y) const;
        void SetPixel(int x, int y, Pixel p);
        void Hista(int hist[256], char channel) const;
        void iluminas() const;
        void White_Balance() const;

    private:
        int height = 0;
        int width = 0;
        Pixel pixels[4000000];
    };
}

#endif
