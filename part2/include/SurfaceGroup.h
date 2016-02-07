#ifndef SURFACEGROUP_H_
#define SURFACEGROUP_H_

#include "Surface.h"
#include "Ray.h"
#include "Intersection.h"

#include <vector>

struct SurfaceGroup {
    std::vector<Surface*> surfaces;

    void add(Surface* surface);
    
    Intersection* intersect(const Ray& ray);
}

#endif
