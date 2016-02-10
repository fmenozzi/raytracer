#include "Plane.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>

#include <cstdio>

Intersection Plane::intersect(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;
    Vector3 a(0,-2,0);  // TODO: Need a general way of finding point on plane

    Intersection i(this, n, 0, false);

    if (n.dot(d) <= 0.0) {
        i.t     = (a-p).dot(n) / d.dot(n);
        i.valid = true;
    }

    return i;
}
