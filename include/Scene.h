#ifndef SCENE_H_
#define SCENE_H_

#include "SurfaceGroup.h"

class Intersection;
class Ray;

struct Scene {
    SurfaceGroup& surfaces;
   
    Scene(SurfaceGroup& _surfaces) :
       surfaces(_surfaces) {}

    Intersection* intersect(const Ray& ray);
};

#endif
