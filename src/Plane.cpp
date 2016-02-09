#include "Plane.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>

#include <cstdio>

Intersection* Plane::intersect(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;

    // TODO: Used to be <
    if (n.dot(d) > 0.0f) {
        return nullptr;
    } else {
        // TODO: Need general way of finding point on plane
        Vector3 a(0,-2,0);
        float t = (a-p).dot(n) / d.dot(n);
        return new Intersection(this, n, t);
    }
}
