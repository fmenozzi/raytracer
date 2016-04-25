#include "Plane.h"
#include "Ray.h"
#include "Intersection.h"

#include <Eigen/Dense>

std::unique_ptr<Intersection> Plane::intersect(const Ray& ray) {
    auto p = ray.p;
    auto d = ray.d;

    if (n.dot(d) > 0.0f) {
        return nullptr;
    } else {
        auto a = this->p;
        float t = (a-p).dot(n) / d.dot(n);
        return std::unique_ptr<Intersection>(new Intersection(this, n, t));
    }
}
