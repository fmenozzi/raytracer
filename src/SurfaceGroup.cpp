#include "SurfaceGroup.h"
#include "Intersection.h"

void SurfaceGroup::add(Surface* surface) {
    surfaces.push_back(surface);
}

Intersection* SurfaceGroup::intersect(const Ray& ray) {
    Intersection* result = nullptr;
    for (const auto& surface : surfaces) {
        Intersection* hit = surface->intersect(ray);
        if (hit) {
            if (result)
                delete result;
            result = hit;
        }
    }
    return result;
}
