#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>

struct Color {
    uint8_t r, g, b;

    Color() : r(0), g(0), b(0) {}
    Color(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}
};

#endif
