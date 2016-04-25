#ifndef SCENE_H_
#define SCENE_H_

#include "Light.h"
#include "Color.h"
#include "Intersection.h"

#include <memory>

struct SurfaceList;
struct Ray;

struct Scene {
    SurfaceList& surfaces;
    Light light;
   
    Scene(SurfaceList& _surfaces, const Light& _light) :
        surfaces(_surfaces),
        light(_light) {}

    std::unique_ptr<Intersection> intersect(const Ray& ray) const;
    Color shade(const Ray& ray, const Intersection& hit, int depth, bool shadows, bool kd) const;
};

#endif
