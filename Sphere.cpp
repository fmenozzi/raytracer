#include "Sphere.h"
#include "Ray.h"
#include "Vector3.h"

#include <cmath>

bool Sphere::intersects(const Ray& ray) {
    Vector3 p = ray.p;
    Vector3 d = ray.d;

    float dp = d.dot(p);
    float dd = d.dot(d);
    float pp = p.dot(p);

    float det = (dp*dp) - (dd*(pp-(radius*radius)));

    return det > 0;
}
