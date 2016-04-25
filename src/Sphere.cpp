#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"

#include <cmath>

#include <Eigen/Dense>

std::unique_ptr<Intersection> Sphere::intersect(const Ray& ray) {
    auto p = ray.p - center;
    auto d = ray.d;

    float dp = d.dot(p);
    float dd = d.dot(d);
    float pp = p.dot(p);

    float discr = (dp*dp) - (dd*(pp-(radius*radius)));

    if (discr < 0) {
        return nullptr;
    } else {
        // Find both intersections
        float t0 = (-dp - sqrt(discr)) / dd;
        float t1 = (-dp + sqrt(discr)) / dd;

        // Entire sphere is behind camera
        if (t1 < 0)
            return nullptr;

        // Front of sphere is behind camera
        float t = t0 < 0 ? t1 : t0;

        // Calculate surface normal
        auto n = (ray.evaluate(t) - center).normalized();

        return std::unique_ptr<Intersection>(new Intersection(this, n, t));
    }
}
