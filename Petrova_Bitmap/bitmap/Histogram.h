#ifndef BITMAP_HISTOGRAM_H
#define BITMAP_HISTOGRAM_H

namespace Pictures {
    double hist_mean(const int hist[256], const int count);
    int hist_median(const int hist[256], const int count);
}

#endif
