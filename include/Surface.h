#ifndef SURFACE_H_
#define SURFACE_H_

#include "Material.h"
#include "Color.h"
#include "Intersection.h"

#include <memory>

#include <Eigen/Dense>

struct Ray;
struct Light;
struct SurfaceList;
struct Scene;

struct Surface {
    Material mat;

    Surface(const Material& _mat) : mat(_mat) {}
    virtual ~Surface() {}

    virtual std::unique_ptr<Intersection> intersect(const Ray& ray) = 0;

    Color shade(const Ray& ray, const Eigen::Vector3f& point, const Eigen::Vector3f& n,
                const Light& light, const Scene& scene, int depth, bool shadows, bool kd);
    
};

#endif
