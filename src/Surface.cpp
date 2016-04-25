#include "Surface.h"
#include "Ray.h"
#include "Light.h"
#include "SurfaceList.h"
#include "Intersection.h"
#include "Scene.h"
#include "KD.h"

#include <algorithm>

#include <Eigen/Dense>

void calculate_Ld_Ls(const Ray& ray, const Ray& lightray, float I,
                     const Eigen::Vector3f& n, const Material& mat,
                     Color& Ld, Color& Ls) {
    auto v = -ray.d.normalized();
    auto l = lightray.d.normalized();
    auto h = (v+l).normalized();

    Ld = mat.kd * I * std::max(0.0f, n.dot(l));
    Ls = mat.ks * I * std::pow(std::max(0.0f, n.dot(h)), mat.sp);
}

Color Surface::shade(const Ray& ray, const Eigen::Vector3f& point, const Eigen::Vector3f& n,
                     const Light& light, const Scene& scene, int depth, bool shadows, bool kd) {
    Color La, Ld, Ls, Lm;

    La = mat.ka * light.intensity;

    float I = light.intensity;

    auto corrected_point = point + n*0.01f;
    auto lightray = Ray(corrected_point, light.pos - corrected_point);

    // Apply diffuse and specular shading, with shadows, if applicable
    if (shadows) {
        std::unique_ptr<Intersection> lighthit;
        if (kd)
            lighthit = std::unique_ptr<Intersection>(kd_intersect(ray, kd_tree, 0, mat).intersect(lightray));
        else
            lighthit = std::unique_ptr<Intersection>(scene.intersect(lightray));

        if (!lighthit)
            calculate_Ld_Ls(ray, lightray, I, n, mat, Ld, Ls);
    } else {
        calculate_Ld_Ls(ray, lightray, I, n, mat, Ld, Ls);
    }

    // Apply recursive raytracing, if applicable
    if (mat.a != 0.0f && depth != 0) {
        auto v = -ray.d.normalized();
        auto r = -v - 2*((-v).dot(n)*n);

        auto reflected_ray = Ray(corrected_point, r);
        auto hit = scene.intersect(reflected_ray);
        if (hit)
            Lm = scene.shade(reflected_ray, *hit, depth-1, shadows, kd);
    }

    return (La + Ld + Ls)*(1-mat.a) + (Lm)*(mat.a);
}
