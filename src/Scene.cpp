#include "Scene.h"
#include "Intersection.h"
#include "Ray.h"
#include "Surface.h"
#include "SurfaceList.h"

#include <Eigen/Dense>

std::unique_ptr<Intersection> Scene::intersect(const Ray& ray) const {
    return surfaces.intersect(ray);
}

Color Scene::shade(const Ray& ray, const Intersection& hit, int depth, bool shadows, bool kd) const {
    auto p = ray.evaluate(hit.t); 
    auto n = hit.normal;

    return (hit.hit)->shade(ray, p, n, light, *this, depth, shadows, kd);
}
