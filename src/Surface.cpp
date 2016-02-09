#include "Surface.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "SurfaceList.h"

#include <algorithm>

// TODO: Add "LightGroup" that contains vector of Lights

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
        Vector3 v = ray.d * -1;
        Vector3 l = (light.pos - corrected_point) * -1;
        Vector3 h = (v+l).norm();

        float I = light.intensity;
        Color Ld = mat.kd * I * std::max(0.f, normal.dot(l));
        Color Ls = mat.ks * I * std::max(0.f, std::pow(normal.dot(h), mat.sp));
        Color La = mat.ka * I;

        // (0,0,0), (0,0,0), (.2,.2,.2)
        //printf("(Ld=(%.2f, %.2f, %.2f), Ls=(%.2f, %.2f, %.2f), La=(%.2f, %.2f, %.2f))\n",
     //           Ld.r, Ld.g, Ld.b, Ls.r, Ls.g, Ls.b, La.r, La.g, La.b);

        res = res + Ld + Ls + La;
    }

    //printf("(%f, %f, %f)\n", res.r, res.g, res.b);

    return res;
}
