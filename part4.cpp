#include <cstdio>

#if defined(USE_OPENGL)
    #include <GL/glut.h>
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

constexpr int NX = 512;
constexpr int NY = 512;

Color* buffer;

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

int main(int argc, char* argv[]) {
    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float dist = 0.1f;

    // Materials
    Material mp(Color(0.2f, 0.2f, 0.2f), Color(1.0f, 1.0f, 1.0f), Color(0.0f, 0.0f, 0.0f),  0.0f, 0.5f);
    Material m1(Color(0.2f, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f),  0.0f, 0.0f);
    Material m2(Color(0.0f, 0.2f, 0.0f), Color(0.0f, 0.5f, 0.0f), Color(0.5f, 0.5f, 0.5f), 32.0f, 0.0f);
    Material m3(Color(0.0f, 0.0f, 0.2f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 0.0f),  0.0f, 0.8f);

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
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float u = l + ((r-l)*(i+0.5f)/NX);
            float v = b + ((t-b)*(j+0.5f)/NY);

            auto p = Eigen::Vector3f(0, 0, 0);
            auto d = Eigen::Vector3f(u, v, -dist);

            auto ray = Ray(p, d);

            auto hit = std::unique_ptr<Intersection>(scene.intersect(ray));
            if (hit)
                buffer[i*NY + j] = scene.shade(ray, *hit, 2, true, false).correct(2.2f);
        }
    }

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        glutCreateWindow("Part 4");
        glutDisplayFunc(gl_display);
        glutKeyboardFunc(gl_keyboard);
        glutMainLoop();
    #else
        // Write buffer to image file
        const char* path = "images/part4.ppm";
        FILE* fp = fopen(path, "w");
        fprintf(fp, "P3\n");
        fprintf(fp, "%d %d %d\n", NX, NY, 255);
        for (int i = NX-1; i >= 0; i--) {
            for (int j = 0; j < NY; j++) {
                // Convert float RGB to int RGB
                int ir = (int)(buffer[j*NY + i].r * 255);
                int ig = (int)(buffer[j*NY + i].g * 255);
                int ib = (int)(buffer[j*NY + i].b * 255);

                fprintf(fp, "%d %d %d\n", ir, ig, ib);
            }
        }
        fclose(fp);
        printf("Image written to %s\n", path);
    #endif

    delete[] buffer;

    return 0;
}