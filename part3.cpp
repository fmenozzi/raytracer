#include <cstdio>
#include <cstdlib>

#if defined(USE_OPENGL)
    #include <GL/glut.h>
#endif

#if defined(USE_OPENMP)
    #include "omp.h"
#endif

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
#endif

int main(int argc, char* argv[]) {
    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float dist = 0.1f;

    constexpr int SAMPLES   = 64;

    const int SAMPLEDIM = sqrt(SAMPLES);

    // Materials
    Material mp(Color(0.2f, 0.2f, 0.2f), Color(1.0f, 1.0f, 1.0f), Color(0.0f, 0.0f, 0.0f),  0.0f);
    Material m1(Color(0.2f, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f), Color(0.0f, 0.0f, 0.0f),  0.0f);
    Material m2(Color(0.0f, 0.2f, 0.0f), Color(0.0f, 0.5f, 0.0f), Color(0.5f, 0.5f, 0.5f), 32.0f);
    Material m3(Color(0.0f, 0.0f, 0.2f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 0.0f),  0.0f);

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

                Vector3 p(0,0,0);
                Vector3 d(u, v, -dist);

                Ray ray(p, d);

                Intersection* hit = scene.intersect(ray);
                if (hit)
                    res += scene.shade(ray, hit).correct(2.2f);
                delete hit;
            }
        }
        buffer[i*NY + j] = res / SAMPLES;
    }

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        glutCreateWindow("Part 3");
        glutDisplayFunc(gl_display);
        glutMainLoop();
    #else
        // Write buffer to image file
        FILE* fp = fopen("images/part3.ppm", "w");
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
