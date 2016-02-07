#ifndef PLANE_H_
#define PLANE_H_

#include "Vector3.h"
#include "Ray.h"

struct Plane {
    Vector3 a;
    Vector3 n;

    Plane(const Vector3& _a, const Vector3& _n) : a(_a), n(_n) {}

    bool intersects(const Ray& ray);
};

#endif
