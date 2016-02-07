#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

struct Vector3 {
    float x,y,z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3& v) const { return Vector3(x+v.x, y+v.y, z+v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x-v.x, y-v.y, z-v.z); }
    Vector3 operator*(float n) const { return Vector3(n*x, n*y, n*z); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }

    Vector3 norm() {
        float n = 1 / sqrt(x*x + y*y + z*z);
        return Vector3(n*x, n*y, n*z);
    }

    float dot(const Vector3& v) const {
        return x*v.x + y*v.y + z*v.z;
    }
};

#endif
