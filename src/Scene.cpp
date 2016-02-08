#include "Scene.h"
#include "Intersection.h"
#include "Ray.h"

Intersection* Scene::intersect(const Ray& ray) {
    return surfaces.intersect(ray);
}

Color Scene::shade(const Ray& ray, Intersection* hit) {
    Vector3 p = ray.evaluate(hit.t);
    Vector3 n = hit.normal;

    return (hit.hit)->shade(ray, p, n, light, surfaces);
}
