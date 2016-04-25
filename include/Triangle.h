#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Surface.h"
#include "Material.h"
#include "Intersection.h"

#include <memory>

#include <Eigen/Dense>

struct Ray;

struct Triangle : public Surface {
    Eigen::Vector3f a;
    Eigen::Vector3f b;
    Eigen::Vector3f c;

    Eigen::Vector3f n;

    Triangle(const Eigen::Vector3f& _a, const Eigen::Vector3f& _b, const Eigen::Vector3f& _c, const Eigen::Vector3f& _n, const Material& _mat) :
        Surface(_mat),
        a(_a),
        b(_b),
        c(_c),
        n(_n) {}

    std::unique_ptr<Intersection> intersect(const Ray& ray) override;
};

#endif
