#include "Bitmap.h"
#include "Histogram.h"
#include <iostream>

namespace Pictures {

    void Bitmap::SetSize(int w, int h){width = w; height = h;}

    Pixel Bitmap::GetPixel(int x,int y)const{return pixels[y*width+x]; }
    void Bitmap::SetPixel(int x, int y, Pixel p){ pixels[width*y +x]=p;}

    void Bitmap::Hista(int hist[256], char channel)const{
        for(int i = 0; i < 256; i++){hist[i]=0;}
        for(int px = 0; px < height * width; px++){
            int v = 0; //число цвета 
            if(channel == 'Y'){v = static_cast<int>(pixels[px].Y +0.5);}
            if(channel == 'B'){v = pixels[px].B;}
            if(channel == 'R'){v = pixels[px].R;}
            if(channel == 'G'){v = pixels[px].G;}
            hist[v]++ ;  //в это ячейке количество пикселей с этим конкретным значением,типо ну вот ячейка где синий 200, и там лежит 10 пикселей
        }
    }

    void Bitmap::iluminas()const{
        int hist[256];
        Hista(hist, 'Y');
        std::cout <<"Ekspozitsiya: srednyaya Y: " << hist_mean(hist, width*height)<< " mediana: "<< hist_median(hist, width*height)<< std::endl;
    }

    void Bitmap::White_Balance()const{
        const char channels[3] = {'R','G','B'};
        double avg[3]; //average - crednee
        for(int c = 0;c < 3;c++){
            int hist[256];//на каждом круге создаём новую гисту
            Hista(hist, channels[c]);
            avg[c] = hist_mean(hist, width*height);
            std::cout<<"Balans belogo: "<<channels[c]<<": srednee: "<<avg[c]<<" mediana: "<<hist_median(hist, width*height)<<std::endl;
        }
    }

}
