#include "Plane.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>

#include <cstdio>

Intersection* Plane::intersect(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;

    if (n.dot(d) < 0.0f) {
        return nullptr;
    } else {
        float t = (p.dot(n) + this->d) / d.dot(n);
        return new Intersection(this, n, t);
    }
}
