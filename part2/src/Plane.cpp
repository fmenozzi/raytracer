#include "Plane.h"

#include <cmath>

#include <cstdio>

bool Plane::intersects(const Ray& ray) {
    return fabs(n.dot(ray.d)) > 0.01;
}
