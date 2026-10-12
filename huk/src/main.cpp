#include <filesystem>
#include <iostream>

#include "Pictures/Bitmap.h"
#include "Pictures/BmpReader.h"
#include "Pictures/BmpView.h"
#include "Pictures/Bytes.h"
#include "Pictures/utility/FileLoader.h"
#include "Pictures/Pixel.h"

using namespace Pictures;

static int process_file(const char* path) {
    unsigned char h[54] {};
    if (!utility::load_file_bytes(path, h, 54)) {
        std::cerr << "Не удалось открыть или прочитать файл: " << path << std::endl;
        return 1;
    }

    if (h[0] != 'B' || h[1] != 'M') {
        std::cerr << "Это не BMP файл (нет сигнатуры BM): " << path << std::endl;
        return 1;
    }

    const int size = static_cast<int>(std::filesystem::file_size(path));

    const int file_size        = select_4_bites(h + 2);
    const int data_offset      = select_4_bites(h + 10);
    const int info_header_size = select_4_bites(h + 14);
    const int width            = select_4_bites(h + 18);
    const int height           = select_4_bites(h + 22);
    const int planes           = select_2_bites(h + 26);
    const int bits_per_pixel   = select_2_bites(h + 28);
    const int compression      = select_4_bites(h + 30);
    const int image_size       = select_4_bites(h + 34);
    const int x_pixels_per_m   = select_4_bites(h + 38);
    const int y_pixels_per_m   = select_4_bites(h + 42);
    const int colors_used      = select_4_bites(h + 46);
    const int colors_important = select_4_bites(h + 50);

    if (info_header_size < 40 || width <= 0 || height == 0 || planes != 1) {
        std::cerr << "Файл повреждён или неподдерживаемый формат заголовка" << std::endl;
        return 1;
    }
    if (size < 54 || width > size || height > size || height < -size || data_offset < 54 || data_offset > size) {
        std::cerr << "Файл повреждён: размеры в заголовке не сходятся с размером файла" << std::endl;
        return 1;
    }
    const int rows = height < 0 ? -height : height;
    const int row_bytes = (bits_per_pixel * width + 7) / 8;
    if (rows > (size - data_offset) / row_bytes) {
        std::cerr << "Файл повреждён: пикселей меньше, чем указано в заголовке" << std::endl;
        return 1;
    }

    std::cout << "2b headers.bitmap_signature : " << h[0] << h[1] << std::endl;
    std::cout << "4b headers.bitmap_file_size : " << file_size << std::endl;
    std::cout << "4b headers.bitmap_data_offset : " << data_offset << std::endl;
    std::cout << "4b headers.bitmap_info_header_size : " << info_header_size << std::endl;
    std::cout << "4b headers.bitmap_width : " << width << std::endl;
    std::cout << "4b headers.bitmap_height : " << height << std::endl;
    std::cout << "2b headers.bitmap_planes : " << planes << std::endl;
    std::cout << "2b headers.bitmap_bits_per_pixel : " << bits_per_pixel << std::endl;
    std::cout << "4b headers.bitmap_compression : " << compression << std::endl;
    std::cout << "4b headers.bitmap_image_size : " << image_size << std::endl;
    std::cout << "4b headers.bitmap_XpixelsPerM : " << x_pixels_per_m << std::endl;
    std::cout << "4b headers.bitmap_YpixelsPerM : " << y_pixels_per_m << std::endl;
    std::cout << "4b headers.bitmap_ColorsUsed : " << colors_used << std::endl;
    std::cout << "4b headers.bitmap_ColorsImportant : " << colors_important << std::endl;

    if (compression != 0) {
        std::cerr << "Сжатые BMP (compression != 0) не поддерживаются" << std::endl;
        return 1;
    }
    const int bpp = bits_per_pixel;
    if (bpp != 1 && bpp != 4 && bpp != 8 && bpp != 24 && bpp != 32) {
        std::cerr << "Неподдерживаемая глубина цвета: " << bpp << std::endl;
        return 1;
    }

    unsigned char* data = new unsigned char[size] {};
    utility::load_file_bytes(path, data, size);

  
    const BmpView bmp { data, size, data_offset, info_header_size, width, rows, height > 0, bpp };
    std::cout << std::endl;
    print_corner(bmp, "Левый верхний: ",  0,         0);
    print_corner(bmp, "Правый верхний:", width - 1, 0);
    print_corner(bmp, "Левый нижний:  ",  0,         rows - 1);
    print_corner(bmp, "Правый нижний: ", width - 1, rows - 1);


    static Bitmap image;
    image.SetSize(width, rows);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < width; x++) {
            Pixel p{};
            read(bmp, x, y, p);
            image.SetPixel(x, y, p);
        }
    }
    std::cout << std::endl;
    image.iluminas();
    image.White_Balance();

    delete[] data;
    return 0;
}

int main(const int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "image.bmp";

    if (std::filesystem::is_directory(path)) {
        int total = 0;
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const auto extension = entry.path().extension();
            if (extension != ".bmp" && extension != ".BMP") { continue; }
            std::cout << "===== " << entry.path().filename().string() << " =====" << std::endl;
            process_file(entry.path().string().c_str());
            std::cout << std::endl;
            total++;
        }
        std::cout << "Faylov: " << total << std::endl;
        return 0;
    }

    return process_file(path);
}
