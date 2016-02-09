#include <cstdio>

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Surface.h"
#include "SurfaceList.h"
#include "Sphere.h"
#include "Plane.h"
#include "Intersection.h"
#include "Scene.h"

/*
 * TODO: 
 *
 * Here's the problem: I've been using a coordinate system that uses
 * the UPPER-left corner, while the uv-conversion in the text uses an
 * origin in the LOWER-left corner. My y dimension is therefore flipped.
 *
 * Need to fix that, keeping in mind that I need to provide data to .ppm
 * files starting from the upper left
 */

int main() {
    constexpr int NX = 512;
    constexpr int NY = 512;

    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float dist = 0.1f;

    // Materials
    Material mp(Color(0.2, 0.2, 0.2), Color(1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0),  0.0);
    Material m1(Color(0.2, 0.0, 0.0), Color(1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0),  0.0);
    Material m2(Color(0.0, 0.2, 0.0), Color(0.0, 0.5, 0.0), Color(0.5, 0.5, 0.5), 32.0);
    Material m3(Color(0.0, 0.0, 0.2), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 0.0),  0.0);

    // Surfaces
    SurfaceList surfaces;
    surfaces.add(new Plane(0, 1, 0, 2, mp));
    surfaces.add(new Sphere(Vector3(-4, 0, -7), 1, m1));
    surfaces.add(new Sphere(Vector3( 0, 0, -7), 2, m2));
    surfaces.add(new Sphere(Vector3( 4, 0, -7), 1, m3));

    // Light
    Light light(Vector3(-4, 4, -3), 1);

    // Add surfaces and light to scene
    Scene scene(surfaces, light);

    // Fill pixel buffer
    //Color* buffer = new Color[NX*NY];   // TODO: Figure out how to increase stack size
    Color buffer[NX][NY];
    //for (int k = 0; k < NX*NY; k++) {
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            /*
            int x = k % NX;
            int y = k / NX;

            float u = l + ((r-l)*(x+0.5f)/NX);
            float v = b + ((t-b)*(y+0.5f)/NY);
            */

            float u = l + ((r-l)*(i+0.5f)/NX);
            float v = b + ((t-b)*(j+0.5f)/NY);

            Vector3 p(0,0,0);
            Vector3 d(u, v, -dist);

            Ray ray(p, d);

            Intersection* hit = scene.intersect(ray);
            if (hit)
                buffer[i][j] = scene.shade(ray, hit).correct(2.2);
            delete hit;
        }
    }
    //}

    // Write buffer to image file
    FILE* fp = fopen("images/part2.ppm", "w");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d %d\n", NX, NY, 255);
    //for (int k = 0; k < NX*NY; k++) {
    for (int i = NX-1; i >= 0; i--) {
        for (int j = 0; j < NY; j++) {
            // Convert float RGB to int RGB
            int ir = (int)(buffer[j][i].r * 255);
            int ig = (int)(buffer[j][i].g * 255);
            int ib = (int)(buffer[j][i].b * 255);

            fprintf(fp, "%d %d %d\n", ir, ig, ib);
        }
    }
    //}
    fclose(fp);

    //delete[] buffer;

    return 0;
}
