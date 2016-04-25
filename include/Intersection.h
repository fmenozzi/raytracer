#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <Eigen/Dense>

struct Surface;

struct Intersection {
    Surface* hit;
    Eigen::Vector3f normal;
    float t;

    Intersection(Surface* _hit, const Eigen::Vector3f& _normal, float _t) :
        hit(_hit),
        normal(_normal),
        t(_t) {}
};

#endif
