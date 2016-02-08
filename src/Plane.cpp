#include "Plane.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>

Intersection* Plane::intersect(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;

    if (n.dot(d) < 0.0f) {
        return nullptr;
    } else {
        // TODO: Bogus t for now

        float t = 0;

        return new Intersection(this, n, t);
    }
}
