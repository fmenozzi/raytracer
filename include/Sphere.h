#ifndef SPHERE_H_
#define SPHERE_H_

#include "Surface.h"
#include "Vector3.h"
#include "Material.h"

class Intersection;
class Ray;

struct Sphere : public Surface {
    Vector3 center;
    float radius;

    Sphere(const Vector3& _center, float _radius, Material _mat) : 
        Surface(_mat),
        center(_center),
        radius(_radius) {}

    Intersection* intersect(const Ray& ray) override;
};

#endif
