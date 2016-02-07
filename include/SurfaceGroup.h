#ifndef SURFACEGROUP_H_
#define SURFACEGROUP_H_

#include <vector>

class Surface;
class Intersection;
class Ray;

struct SurfaceGroup {
    std::vector<Surface*> surfaces;

    void add(Surface* surface);
    
    Intersection* intersect(const Ray& ray);
};

#endif
