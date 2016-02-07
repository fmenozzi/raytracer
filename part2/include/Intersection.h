#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Vector3.h"

class Surface;

struct Intersection {
    Surface* hit;
    Vector3 normal;
    float t;

    Intersection(Surface* _hit, const Vector3& _normal, float _t) :
        hit(_hit),
        normal(_normal),
        t(_t) {}
};

#endif
