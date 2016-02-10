#include "SurfaceList.h"
#include "Intersection.h"

void SurfaceList::add(Surface* surface) {
    surfaces.push_back(surface);
}

// TODO: Image renders incorrectly when I take first hit
//       instead of last
Intersection SurfaceList::intersect(const Ray& ray) const {
    Intersection result(nullptr, Vector3(0,0,0), 0, false);
    for (const auto& surface : surfaces) {
        Intersection hit = surface->intersect(ray);
        if (hit.valid)
            result = hit;
    }
    return result;
}
