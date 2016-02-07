#include <cstdio>

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Surface.h"
#include "Sphere.h"
#include "Plane.h"
#include "Intersection.h"

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
    Surface* pl = new Plane(0, 1, 0, 2, mp);
    Surface* s1 = new Sphere(Vector3(-4, 0, -7), 1, m1);
    Surface* s2 = new Sphere(Vector3( 0, 0, -7), 1, m2);
    Surface* s3 = new Sphere(Vector3(-4, 0, -7), 1, m3);

    Color buffer[NX][NY];

    // Fill pixel buffer
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float u = l + ((r-l)*(i+0.5f)/NX);
            float v = b + ((t-b)*(j+0.5f)/NY);

            Vector3 p(0,0,0);
            Vector3 d(u, v, -dist);

            Ray ray(p, d);

            if (pl->intersect(ray) != nullptr) buffer[i][j] = Color(255, 255, 255);
            if (s1->intersect(ray) != nullptr) buffer[i][j] = Color(255, 255, 255);
            if (s2->intersect(ray) != nullptr) buffer[i][j] = Color(255, 255, 255);
            if (s3->intersect(ray) != nullptr) buffer[i][j] = Color(255, 255, 255);
        }
    }

    delete pl;
    delete s1;
    delete s2;
    delete s3;

    // Write buffer to image file
    FILE* fp = fopen("../images/part2.ppm", "w");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d %d\n", NX, NY, 255);
    for (int i = 0; i < NX; i++)
        for (int j = 0; j < NY; j++)
            fprintf(fp, "%d %d %d\n", buffer[j][i].r, buffer[j][i].g, buffer[j][i].b);
    fclose(fp);

    return 0;
}
