#ifndef PLANE_H_
#define PLANE_H_

#include "Surface.h"
#include "Material.h"
#include "Intersection.h"

#include <memory>

#include <Eigen/Dense>

struct Ray;

struct Plane : public Surface {
    Eigen::Vector3f p;
    Eigen::Vector3f n;

    Plane(const Eigen::Vector3f& _p, const Eigen::Vector3f& _n, const Material& _mat) :
        Surface(_mat),
        p(_p),
        n(_n) {}

    std::unique_ptr<Intersection> intersect(const Ray& ray) override;
};

#endif
