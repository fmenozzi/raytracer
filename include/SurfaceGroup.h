#ifndef SURFACEGROUP_H_
#define SURFACEGROUP_H_

#include <vector>

#include "Surface.h"

class Intersection;
class Ray;

struct SurfaceGroup {
    std::vector<Surface*> surfaces;

    virtual ~SurfaceGroup() {
        for (auto surface : surfaces)
            delete surface;
    }

    void add(Surface* surface);
    
    Intersection* intersect(const Ray& ray);
};

#endif
