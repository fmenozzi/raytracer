#ifndef RAY_H_
#define RAY_H_

#include <Eigen/Dense>

struct Ray {
    Eigen::Vector3f p;
    Eigen::Vector3f d;

    Ray(const Eigen::Vector3f& _p, const Eigen::Vector3f& _d): p(_p), d(_d.normalized()) {}

    Eigen::Vector3f evaluate(float t) const {
        return p + d*t;
    }
};

#endif
