#include "Sphere.h"
#include "Ray.h"
#include "Vector3.h"

#include <cmath>

float Sphere::intersect(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;

    float pd = p.dot(d);
    float pp = p.dot(p);

    // Returns -1 if no intersection
    float det = pd*pd - pp + radius*radius;
    if (det < 0)
        return -1;

    float sqrtdet = sqrt(det);

    float negpd = (-p).dot(d); // TODO: Are parens here necessary?

    float t0 = negpd + sqrtdet;
    float t1 = negpd - sqrtdet;

    // TODO: Incorporate "dt" adjustment for shadows later on

    return t0<t1 ? t0 : t1;
}
