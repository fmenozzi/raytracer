#include "Surface.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "SurfaceList.h"

#include <algorithm>

Color Surface::shade(const Ray& ray, const Vector3& point, const Vector3& normal, 
                     const Light& light, const SurfaceList& surfaces) {
    // Ambient color of black
    Color res(0,0,0);

    // Shadow correction
    Vector3 corrected_point = point; // + normal*0.01;

    // Generate shadow ray
    Ray shadowray(corrected_point, light.pos - corrected_point);

    // Intersect shadow with surfaces and apply Phong shading
    Intersection* shadowhit = surfaces.intersect(shadowray);
    if (shadowhit) {
        Vector3 v = -ray.d.norm();
        Vector3 l = shadowray.d.norm();
        Vector3 h = (v+l).norm();
        Vector3 n = normal;

        float I = light.intensity;
        Color La = mat.ka * I;
        Color Ld = mat.kd * I * std::max(0.f, n.dot(l));
        Color Ls = mat.ks * I * std::pow(std::max(0.f, n.dot(h)), mat.sp);

        res = res + Ld + Ls + La;
    }

    return res;
}
