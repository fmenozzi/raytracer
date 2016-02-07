#include "Scene.h"
#include "Intersection.h"
#include "Ray.h"

Intersection* Scene::intersect(const Ray& ray) {
    return surfaces.intersect(ray);
}
