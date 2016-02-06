#include <cstdio>

#include "Ray.h"
#include "Vector3.h"
#include "Pixel.h"

int main() {
    constexpr int NX = 512;
    constexpr int NY = 512;

    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float d = 0.1f;

    Vector3 e_(0,0,0);
    Vector3 u_(1,0,0);
    Vector3 v_(0,1,0);
    Vector3 w_(0,0,1);

    Pixel buffer[NX][NY];
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float u = l + (r-l)*(i+0.5f)/NX;
            float v = b + (t-b)*(j+0.5f)/NY;

            Ray ray(e_, u_*u + v_*v - w_*d);
        }
    }

    // Write buffer to image file
    FILE* fp = fopen("part1.ppm", "w");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d %d\n", NX, NY, 255);
    for (int i = 0; i < NX; i++)
        for (int j = 0; j < NY; j++)
            fprintf(fp, "%d %d %d\n", buffer[i][j].r, buffer[i][j].g, buffer[i][j].b);
    fclose(fp);

    return 0;
}
