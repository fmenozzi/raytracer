#ifndef PLANE_H_
#define PLANE_H_

#include "Surface.h"
#include "Vector3.h"
#include "Material.h"

struct Intersection;
struct Ray;

struct Plane : public Surface {
    float a, b, c, d;
    Vector3 n;

    Plane(float _a, float _b, float _c, float _d, Material _mat) : 
        Surface(_mat),
        a(_a), 
        b(_b), 
        c(_c), 
        d(_d), 
        n(Vector3(_a, _b, _c).norm()) {}

    Intersection* intersect(const Ray& ray) override;
};

#endif
