#include "Pictures/Histogram.h"

namespace Pictures {
    double hist_mean(const int hist[256], const int count){ 
        double sum = 0;
        for(int v = 0;v < 256;v++){
            sum += v*(hist[v]);
        }
        return sum/count;       
    }

    int hist_median(const int hist[256], const int count){
        int sum = 0;
        for(int v = 0; v< 256; v++){
            sum+= (hist[v]);
            if(sum >= (count + 1)/2){
                return v;
            }
        }
        return 255; // с++ тупой как пробка и я вмсете с ним 
         
    }
}
