#ifndef SURFACE_H_
#define SURFACE_H_

#include "Material.h"
#include "Color.h"

struct Vector3;
struct Intersection;
struct Ray;
struct Light;
struct SurfaceList;

struct Surface {
    Material mat;

    Surface(Material _mat) : mat(_mat) {}
    virtual ~Surface() {}

    virtual Intersection* intersect(const Ray& ray) = 0;

    Color shade(const Ray& ray, const Vector3& point, const Vector3& n,
                const Light& light, const SurfaceList& surfaces);
    
};

#endif
