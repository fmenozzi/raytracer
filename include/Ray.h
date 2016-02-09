#ifndef RAY_H_
#define RAY_H_

#include "Vector3.h"

struct Ray {
    Vector3 p;
    Vector3 d;

    Ray(const Vector3& _p, const Vector3& _d): p(_p), d(_d.norm()) {}

    Vector3 evaluate(float t) const {
        return p + d*t;
    }
};

#endif
