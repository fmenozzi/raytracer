#include "SurfaceList.h"
#include "Intersection.h"

void SurfaceList::add(Surface* surface) {
    surfaces.push_back(surface);
}

// TODO: Image renders incorrectly when I take first hit
//       instead of last
Intersection* SurfaceList::intersect(const Ray& ray) const {
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
