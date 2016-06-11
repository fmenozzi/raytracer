#include <cstdio>
#include <cstdlib>

#if defined(USE_OPENGL)
    #include <GL/glut.h>
#endif

#if defined(USE_OPENMP)
    #include "omp.h"
#endif

#include "Color.h"
#include "Ray.h"
#include "Surface.h"
#include "SurfaceList.h"
#include "Sphere.h"
#include "Plane.h"
#include "Intersection.h"
#include "Scene.h"

#include <Eigen/Dense>

#include <easyppm.h>

constexpr int NX = 512;
constexpr int NY = 512;

Color* buffer;

PPM ppm;

#if defined(USE_OPENGL)
void gl_display() {
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    float* float_buffer = new float[3*NX*NY];

    int k = 0;
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float_buffer[k++] = buffer[j*NY + i].r;
            float_buffer[k++] = buffer[j*NY + i].g;
            float_buffer[k++] = buffer[j*NY + i].b;
        }
    }

    glDrawPixels(NX, NY, GL_RGB, GL_FLOAT, float_buffer);

    glutSwapBuffers();

    delete[] float_buffer;
}

void gl_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // ESC
        case 27:
            exit(EXIT_SUCCESS);
    }
}
#endif

int clamp(int x, int min, int max) {
    return std::max(min, std::min(x, max));
}

int main(int argc, char* argv[]) {
    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float dist = 0.1f;

    constexpr int SAMPLES   = 64;

    const int SAMPLEDIM = sqrt(SAMPLES);

#ifndef USE_OPENGL
    ppm = easyppm_create(NX, NY, IMAGETYPE_PPM);
#endif

    // Materials
    Material mp(Color(0.2f, 0.2f, 0.2f), Color(1.0f, 1.0f, 1.0f), Color(0.0f, 0.0f, 0.0f),  0.0f, 0.0f);
    Material m1(Color(0.2f, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f),  0.0f, 0.0f);
    Material m2(Color(0.0f, 0.2f, 0.0f), Color(0.0f, 0.5f, 0.0f), Color(0.5f, 0.5f, 0.5f), 32.0f, 0.0f);
    Material m3(Color(0.0f, 0.0f, 0.2f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 0.0f),  0.0f, 0.0f);

    // Surfaces
    SurfaceList surfaces;
    surfaces.add(std::move(std::unique_ptr<Plane>(new Plane(Eigen::Vector3f(0, -2, 0), Eigen::Vector3f(0, 1, 0), mp))));
    surfaces.add(std::move(std::unique_ptr<Sphere>(new Sphere(Eigen::Vector3f(-4, 0, -7), 1, m1))));
    surfaces.add(std::move(std::unique_ptr<Sphere>(new Sphere(Eigen::Vector3f( 0, 0, -7), 2, m2))));
    surfaces.add(std::move(std::unique_ptr<Sphere>(new Sphere(Eigen::Vector3f( 4, 0, -7), 1, m3))));

    // Light
    Light light(Eigen::Vector3f(-4, 4, -3), 1);

    // Add surfaces and light to scene
    Scene scene(surfaces, light);

    // Fill pixel buffer
    buffer = new Color[NX*NY];
    #if defined(USE_OPENMP)
        #pragma omp parallel for
    #endif
    for (int k = 0; k < NX*NY; k++) {
        int i = k % NX;
        int j = k / NX;
        Color res(0,0,0);
        for (int si = 0; si < SAMPLEDIM; si++) {
            for (int sj = 0; sj < SAMPLEDIM; sj++) {
                // Uniform sampling
                float x = (i-0.5f) + (si)/(float)SAMPLEDIM;
                float y = (j-0.5f) + (sj)/(float)SAMPLEDIM;

                float u = l + ((r-l)*(x+0.5f)/NX);
                float v = b + ((t-b)*(y+0.5f)/NY);

                auto p = Eigen::Vector3f(0, 0, 0);
                auto d = Eigen::Vector3f(u, v, -dist);

                auto ray = Ray(p, d);

                auto hit = std::unique_ptr<Intersection>(scene.intersect(ray));
                if (hit)
                    res += scene.shade(ray, *hit, 2, true, false).correct(2.2f);
            }
        }
        #if defined(USE_OPENGL)
            buffer[i*NY + j] = res / SAMPLES;
        #else
            auto color = res / SAMPLES;
            auto r = clamp(color.r * 255, 0, 255);
            auto g = clamp(color.g * 255, 0, 255);
            auto b = clamp(color.b * 255, 0, 255);
            easyppm_set(&ppm, i, j, easyppm_rgb(r, g, b));
        #endif
    }

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        glutCreateWindow("Part 3");
        glutDisplayFunc(gl_display);
        glutKeyboardFunc(gl_keyboard);
        glutMainLoop();
    #else
        // Write buffer to image file
        const char* path = "images/part3.ppm";

        easyppm_invert_y(&ppm);
        easyppm_write(&ppm, path);
        easyppm_destroy(&ppm);

        printf("Image written to %s\n", path);
    #endif

    delete[] buffer;

    return 0;
}
