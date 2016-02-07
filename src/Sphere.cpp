#include "Sphere.h"
#include "Ray.h"
#include "Vector3.h"
#include "Intersection.h"

#include <cmath>

Intersection* Sphere::intersect(const Ray& ray) {
    Vector3 p = ray.p - center;
    Vector3 d = ray.d;

    float dp = d.dot(p);
    float dd = d.dot(d);
    float pp = p.dot(p);

    float discr = (dp*dp) - (dd*(pp-(radius*radius)));

    if (discr < 0) {
        return nullptr;
    } else {
        // TODO: Bogus normal for now
        // TODO: Bogus t for now
        return new Intersection(this, Vector3(0,0,0), 0);
    }
}
