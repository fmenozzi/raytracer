#ifndef SCENE_H_
#define SCENE_H_

#include "Light.h"
#include "Color.h"

class Intersection;
class Ray;
class SurfaceList;

struct Scene {
    SurfaceList& surfaces;
    Light light;
   
    Scene(SurfaceList& _surfaces, const Light& _light) :
        surfaces(_surfaces),
        light(_light) {}

    Intersection* intersect(const Ray& ray);
    Color shade(const Ray& ray, Intersection* hit);
};

#endif
