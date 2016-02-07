#include "Plane.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>

Intersection* Plane::intersect(const Ray& ray) {
    //Vector3 p = ray.p;
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
