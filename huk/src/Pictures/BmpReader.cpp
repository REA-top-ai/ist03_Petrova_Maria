#include "Pictures/BmpReader.h"
#include <iostream>

namespace Pictures {
    void read(const BmpView& bmp, const int x, const int y, Pixel& out){
        const int row_size = ((bmp.bpp * bmp.width + 31) / 32) * 4;//bmp.bpp сколько бит занмает 1 пиксель
        const int file_row = bmp.bottom_up ? bmp.rows - 1 - y : y; // определяем в какой по счёту строке файла
        // записана строка картинки(это не одно и тоже) в картинке строки читаютя сверху вниз , а в bmp снизу вверх
        const int otstup = x * bmp.bpp;//мколько бит нужно оступить от начала строки чтобы дойти до нашего пикселя 
        const int pos = bmp.data_offset + file_row * row_size + otstup / 8;//строка вычисляет номер байта в файле, где находится пиксель, по сути адрес
        const int need = bmp.bpp >= 8 ? bmp.bpp / 8 : 1;

        if (pos + need > bmp.size) { return; }

        int first = pos;                                  // откуда читать B, G, R
        if (bmp.bpp < 24) {                               // палитра: сначала находим запись в ней
            const int shift = 8 - bmp.bpp - otstup % 8;
            const int index = (bmp.data[pos] >> shift) & ((1 << bmp.bpp) - 1);
            first = 14 + bmp.info_header_size + index * 4;
            if (first + 3 >= bmp.data_offset) { return; }
        }
        out.B = bmp.data[first];
        out.G = bmp.data[first + 1];
        out.R = bmp.data[first + 2];
        out.Y = 0.2126 * out.R + 0.7152 * out.G + 0.0722 * out.B;
    }

    void print_corner(const BmpView& bmp, const char* name, const int x, const int y) {
        const int row_size = ((bmp.bpp * bmp.width + 31) / 32) * 4;
        const int file_row = bmp.bottom_up ? bmp.rows - 1 - y : y;
        const int bit_pos = x * bmp.bpp;
        const int pos = bmp.data_offset + file_row * row_size + bit_pos / 8;
        const int need = bmp.bpp >= 8 ? bmp.bpp / 8 : 1;

        int r = 0, g = 0, b = 0;
        bool ok = pos >= 0 && pos + need <= bmp.size;
        if (ok && bmp.bpp >= 24) {
            b = bmp.data[pos];
            g = bmp.data[pos + 1];
            r = bmp.data[pos + 2];
        } else if (ok) {
            const int shift = 8 - bmp.bpp - bit_pos % 8;
            const int index = (bmp.data[pos] >> shift) & ((1 << bmp.bpp) - 1);
            const int entry = 14 + bmp.info_header_size + index * 4;
            ok = entry + 3 < bmp.data_offset;
            if (ok) {
                b = bmp.data[entry];
                g = bmp.data[entry + 1];
                r = bmp.data[entry + 2];
            }
        }

        if (ok) {
            std::cout << name << " R: " << r << " G: " << g << " B: " << b << std::endl;
        } else {
            std::cout << name << " ne udalos prochitat piksel" << std::endl;
        }
    }
}
