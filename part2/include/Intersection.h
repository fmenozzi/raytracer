#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Surface.h"
#include "Vector3.h"

struct Intersection {
    Surface* hit;
    Vector3 normal;
    float t;

    Intersection(Surface* _hit, const Vector3& _normal, float t) :
        hit(hit),
        normal(_normal),
        t(_t);
};

#endif
