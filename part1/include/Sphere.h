#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector3.h"
#include "Ray.h"
#include "Color.h"

struct Sphere {
    Vector3 center;
    float radius;
    Color color;

    Sphere(const Vector3& _center, float _radius, const Color& _color) 
        : center(_center), 
          radius(_radius), 
          color(_color) {}

    bool intersects(const Ray& ray);
};

#endif
