#ifndef COLOR_H_
#define COLOR_H_

struct Color {
    float r, g, b;

    Color() : r(1), g(1), b(1) {}
    Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}

    Color operator+(const Color& c) const { return Color(r+c.r, g+c.g, b+c.b); }
    Color operator*(float f)        const { return Color(f*r, f*g, f*b); }
};

#endif
