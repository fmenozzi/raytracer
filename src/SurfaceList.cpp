#include "SurfaceList.h"
#include "Intersection.h"

#include <algorithm>
#include <iterator>
#include <cfloat>

void SurfaceList::add(std::unique_ptr<Surface> surface) {
    surfaces.push_back(std::move(surface));
}

void SurfaceList::add(SurfaceList& other) {
    surfaces.reserve(surfaces.size() + other.surfaces.size());

    std::move(other.surfaces.begin(),
              other.surfaces.end(),
              std::back_inserter(surfaces));
}

std::unique_ptr<Intersection> SurfaceList::intersect(const Ray& ray) const {
    std::unique_ptr<Intersection> result = nullptr;

    float t = FLT_MAX;
    for (const auto& surface : surfaces) {
        auto hit = surface->intersect(ray);
        if (hit) {
            if (hit->t > 0 && hit->t < t) {
                result = std::move(hit);
                t = result->t;
            }
        }
    }

    return result;
}
