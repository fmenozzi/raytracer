#include "Sphere.h"
#include "Ray.h"
#include "Vector3.h"
#include "Intersection.h"

#include <cmath>

#include <cstdio>

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
        // Find both intersections
        float t0 = (-dp - sqrt(discr)) / dd;
        float t1 = (-dp + sqrt(discr)) / dd;

        // Sphere is behind camera
        if (t1 < 0)
            return nullptr;

        // If t0 is behind camera, use t1
        float t = t0 < 0 ? t1 : t0;

        // Calculate surface normal
        Vector3 n = (ray.evaluate(t) - center).norm();

        return new Intersection(this, n, t);
    }
}
