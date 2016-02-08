#ifndef SCENE_H_
#define SCENE_H_

#include "SurfaceGroup.h"
#include "Color.h"

class Intersection;
class Ray;

struct Scene {
    SurfaceGroup& surfaces;
    Light light;
   
    Scene(SurfaceGroup& _surfaces, const Light& _light) :
        surfaces(_surfaces),
        light(_light) {}

    Intersection* intersect(const Ray& ray);
    Color shade(const Ray& ray, Intersection* hit, const Color& ambient);
};

#endif
