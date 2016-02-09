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
        /*
        Vector3 a(0,0,-2); // TODO: Something more permanent
        float t = (a-p).dot(n) / d.dot(n);
        */

        float t = (p.dot(n) + this->d) / d.dot(n);

        //printf("%f\n", t);

        return new Intersection(this, n, t);
    }
}
