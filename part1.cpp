#include <cstdio>

#include <GL/glut.h>

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Surface.h"
#include "SurfaceList.h"
#include "Sphere.h"
#include "Plane.h"
#include "Intersection.h"
#include "Scene.h"

constexpr int NX = 512;
constexpr int NY = 512;

Color* buffer;

void gl_display() {
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    constexpr int N = 3*NX*NY;

    float* float_buffer = new float[N];

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

int main(int argc, char* argv[]) {
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

    // Add group to scene
    Scene scene(surfaces, light);

    // Fill pixel buffer
    buffer = new Color[NX*NY];
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float u = l + ((r-l)*(i+0.5f)/NX);
            float v = b + ((t-b)*(j+0.5f)/NY);

            Vector3 p(0,0,0);
            Vector3 d(u, v, -dist);

            Ray ray(p, d);

            Intersection* hit = scene.intersect(ray);
            if (hit) 
                buffer[i*NY + j] = Color(1.0, 1.0, 1.0);
            delete hit;
        }
    }

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        glutCreateWindow("Part 1");
        glutDisplayFunc(gl_display);
        glutMainLoop();
    #else
        // Write buffer to image file
        FILE* fp = fopen("images/part1.ppm", "w");
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
    #endif

    delete[] buffer;

    return 0;
}
