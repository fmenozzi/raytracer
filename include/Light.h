#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector3.h"

struct Light {
    Vector3 pos;
    float intensity;

    Light(const Vector3& _pos, float _intensity) :
        pos(_pos),
        intensity(_intensity) {}

    Vector3 directionTo(const Vector3& v);
};

#endif
