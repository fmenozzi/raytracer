#ifndef PLANE_H_
#define PLANE_H_

#include "Surface.h"
#include "Intersection.h"
#include "Vector3.h"
#include "Ray.h"

struct Plane : public Surface {
    Vector3 abc;
    float d;
    Vector3 n;

    Plane(const Vector3& _abc, float _d, const Vector3& _n) : 
        abc(_abc), 
        d(_d), 
        n(_n) {}

    Intersection* intersect(const Ray& ray) override;
};

#endif
