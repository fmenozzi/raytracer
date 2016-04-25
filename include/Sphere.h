#ifndef SPHERE_H_
#define SPHERE_H_

#include "Surface.h"
#include "Material.h"
#include "Intersection.h"

#include <memory>

#include <Eigen/Dense>

struct Ray;

struct Sphere : public Surface {
    Eigen::Vector3f center;
    float radius;

    Sphere(const Eigen::Vector3f& _center, float _radius, const Material& _mat) :
        Surface(_mat),
        center(_center),
        radius(_radius) {}

    std::unique_ptr<Intersection> intersect(const Ray& ray) override;
};

#endif
