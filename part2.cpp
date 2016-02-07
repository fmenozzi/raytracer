#include <cstdio>

#include "Ray.h"
#include "Vector3.h"
#include "Sphere.h"
#include "Color.h"

int main() {
    constexpr int NX = 512;
    constexpr int NY = 512;

    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float dist = 0.1f;

    Sphere s1(Vector3(-4, 0, -7), 1, Color(255, 0, 0));
    Sphere s2(Vector3( 0, 0, -7), 2, Color(0, 255, 0));
    Sphere s3(Vector3( 4, 0, -7), 1, Color(0, 0, 255));

    Color buffer[NX][NY];

    // Fill pixel buffer
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float u = l + ((r-l)*(i+0.5f)/NX);
            float v = b + ((t-b)*(j+0.5f)/NY);

            Vector3 p(0,0,0);
            Vector3 d(u, v, -dist);

            Ray ray(p, d);

            if (s1.intersects(ray))
                buffer[i][j] = s1.color;
            else if (s2.intersects(ray))
                buffer[i][j] = s2.color;
            else if (s3.intersects(ray))
                buffer[i][j] = s3.color;
        }
    }

    // Write buffer to image file
    FILE* fp = fopen("part2.ppm", "w");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d %d\n", NX, NY, 255);
    for (int i = 0; i < NX; i++)
        for (int j = 0; j < NY; j++)
            fprintf(fp, "%d %d %d\n", buffer[j][i].r, buffer[j][i].g, buffer[j][i].b);
    fclose(fp);

    return 0;
}