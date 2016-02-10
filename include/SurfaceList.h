#ifndef SURFACELIST_H_
#define SURFACELIST_H_

#include <vector>

#include "Surface.h"
#include "Intersection.h"

class Ray;

struct SurfaceList {
    std::vector<Surface*> surfaces;

    virtual ~SurfaceList() {
        for (auto surface : surfaces)
            delete surface;
    }

    void add(Surface* surface);
    
    Intersection intersect(const Ray& ray) const;
};

#endif
