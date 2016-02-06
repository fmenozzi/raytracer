#ifndef PIXEL_H_
#define PIXEL_H_

#include <cstdint>

struct Pixel {
    uint8_t r, g, b;

    Pixel() : r(0), g(0), b(0) {}
    Pixel(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}

    static Pixel MakeRGB(uint8_t r, uint8_t g, uint8_t b) {
        Pixel p{r,g,b};
        return p;
    }
};

#endif
