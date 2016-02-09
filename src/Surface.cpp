#include "Surface.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "SurfaceList.h"
#include "Intersection.h"

#include <algorithm>

Color Surface::shade(const Ray& ray, const Vector3& point, const Vector3& n,
                     const Light& light, const SurfaceList& surfaces) {
    // Ambient color
    Color res = mat.ka * light.intensity;

    // Apply shadow correction
    Vector3 corrected_point = point + n*0.01;

    // Generate ray from point to light
    Ray lightray(corrected_point, light.pos - corrected_point);

    // Intersect light ray with surfaces
    Intersection* lighthit = surfaces.intersect(lightray);

    // Apply ambient, diffuse, and specular (Phong) shading
    if (!lighthit) {
        Vector3 v = -ray.d.norm();
        Vector3 l = lightray.d.norm();
        Vector3 h = (v+l).norm();

        float I = light.intensity;
        Color Ld = mat.kd * I * std::max(0.f, n.dot(l));
        Color Ls = mat.ks * I * std::pow(std::max(0.f, n.dot(h)), mat.sp);

        res += Ld + Ls;
    }

    delete lighthit;

    return res;
}
