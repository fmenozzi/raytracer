#ifndef SURFACE_H_
#define SURFACE_H_

#include "Material.h"

class Intersection;
class Ray;

struct Surface {
    Material mat;

    Surface(Material _mat) : mat(_mat) {}
    virtual ~Surface() {}

    virtual Intersection* intersect(const Ray& ray) = 0;
};

#endif
