#include "SurfaceGroup.h"

void SurfaceGroup::add(Surface* surface) {
    surfaces.push_back(surface);
}

Intersection* intersect(const Ray& ray) {
    return nullptr;
}
