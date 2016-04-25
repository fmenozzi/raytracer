#ifndef SURFACELIST_H_
#define SURFACELIST_H_

#include <vector>
#include <memory>

#include "Surface.h"

struct Ray;

struct SurfaceList {
    std::vector<std::unique_ptr<Surface>> surfaces;

    void add(std::unique_ptr<Surface> surface);
    void add(SurfaceList& other);
    
    std::unique_ptr<Intersection> intersect(const Ray& ray) const;
};

#endif
