#include "Triangle.h"
#include "Ray.h"
#include "Intersection.h"

#include <Eigen/Dense>

std::unique_ptr<Intersection> Triangle::intersect(const Ray& ray) {
    auto p = ray.p;
    auto d = ray.d;

    if (n.dot(d) > 0.0f) {
        return nullptr;
    } else {
        // Use centroid as point on plane
        auto pt = 1/3.0f*a + 1/3.0f*b + 1/3.0f*c;

        // Find intersection t
        float t = (pt-p).dot(n) / d.dot(n);

        // Find intersection point
        auto x = p + d*t;

        // Perform intersection tests on half planes
        bool hp0 = (b-a).cross(x-a).dot(n) >= 0;
        bool hp1 = (c-b).cross(x-b).dot(n) >= 0;
        bool hp2 = (a-c).cross(x-c).dot(n) >= 0;

        // Check if point intersects all three halfplanes
        if (hp0 && hp1 && hp2)
            return std::unique_ptr<Intersection>(new Intersection(this, n, t));

        return nullptr;
    }
}
