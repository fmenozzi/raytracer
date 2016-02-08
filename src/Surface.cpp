#include "Surface.h"
#include "Vector3.h"
#include "Ray.h"
#include "Light.h"
#include "SurfaceGroup.h"

// TODO: Add "LightGroup" that contains vector of Lights

Color Surface::shade(const Ray& ray, const Vector3& point, const Vector3& n, 
                     const Light& light, const SurfaceGroup& surfaces) {
    // Ambient color of black
    Color res(0,0,0);

    // Shadow correction
    Vector3 corrected_point = point + normal*100;

    // Generate shadow ray
    Ray shadowray(corrected_point, light.pos - corrected_point);

    // Intersect shadow with surfaces and apply Phong shading
    Intersection* shadowhit = surfaces.intersect(shadowray);
    if (!shadowhit) {

    }

    return Color(0,0,0);
}
