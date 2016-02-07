#include "Plane.h"

#include <cmath>

Intersection* Plane::intersects(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;

    // TODO: Use better floating point comparison
    if (n.dot(d) == 0.0f) {
        return nullptr;
    } else {
        // TODO: Bogus normal for now
        // TODO: Bogus t for now
        return new Intersection(this, Vector3(0,0,0), 0);
    }
}
