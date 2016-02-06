#include <cstdio>

#include "Pixel.h"

int main() {
    constexpr int W = 512;
    constexpr int H = 512;

    // Frame buffer
    Pixel buffer[W][H];

    // Write buffer to image file
    FILE* fp = fopen("part1.ppm", "w");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d %d\n", W, H, 255);
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
            fprintf(fp, "%d %d %d\n", buffer[i][j].r, buffer[i][j].g, buffer[i][j].b);
    fclose(fp);

    return 0;
}
