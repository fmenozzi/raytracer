#include "Surface.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "SurfaceGroup.h"

Color Surface::shade(const Ray& ray, const Vector3& point, const Vector3& n, 
                     const Light& light, const SurfaceGroup& surfaces) {
    return Color(0,0,0);
}
