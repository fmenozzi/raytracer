#ifndef SPHERE_H_
#define SPHERE_H_

#include "Surface.h"
#include "Intersection.h"
#include "Vector3.h"
#include "Ray.h"
#include "Color.h"

struct Sphere : public Surface {
    Vector3 center;
    float radius;
    Color color;

    Sphere(const Vector3& _center, float _radius, const Color& _color) 
        : center(_center), 
          radius(_radius), 
          color(_color) {}

    Intersection* intersect(const Ray& ray) override;
};

#endif
