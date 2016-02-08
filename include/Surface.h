#ifndef SURFACE_H_
#define SURFACE_H_

#include "Material.h"
#include "Color.h"

class Intersection;
class Ray;

struct Surface {
    Material mat;

    Surface(Material _mat) : mat(_mat) {}
    virtual ~Surface() {}

    virtual Intersection* intersect(const Ray& ray) = 0;
    Color shade(const Ray& ray, const Vector3& point, const Vector3& n, 
                const Light& light, const SurfaceGroup& surfaces);
    
};

#endif
