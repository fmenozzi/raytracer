#ifndef SURFACE_H_
#define SURFACE_H_

#include "Material.h"

struct Surface {
    Material mat;

    virtual Intersection* intersect(const Ray& ray) = 0;
}

#endif
