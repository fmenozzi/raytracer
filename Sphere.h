#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector3.h"
#include "Ray.h"

struct Sphere {
    Vector3 center;
    float radius;

    Sphere(const Vector3& _center, float _radius) : center(_center), radius(_radius) {}

    float intersect(const Ray& ray);
};

#endif
