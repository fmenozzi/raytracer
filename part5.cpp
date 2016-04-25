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
#include "Triangle.h"
#include "Intersection.h"
#include "Scene.h"
#include "KD.h"
#include "Mesh.h"

#include <Eigen/Dense>

#include <argparser.h>

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
    int shadows = 0;
    
    argparser ap = argparser_create(argc, argv, PARSEMODE_LENIENT);
    argparser_add(&ap, "-s", "--shadows", ARGTYPE_BOOL, &shadows, NULL);
    argparser_parse(&ap);

    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;

    constexpr float dist = 0.1f;

    // Load mesh into k-d tree
    mesh_load("sibenik.obj");
    kd_load("kdtree.simple", kd_tree);

    // Light
    auto light = Light(Eigen::Vector3f(0,0,0), 1);

    // All triangles share the same material
    Material mt(Color(0,0,0), Color(1,1,1), Color(0,0,0), 0, 0);

    // Fill pixel buffer
    buffer = new Color[NX*NY];
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            float uu = l + ((r-l)*(i+0.5f)/NX);
            float vv = b + ((t-b)*(j+0.5f)/NY);

            auto e = Eigen::Vector3f( 0, -10,   0);
            auto u = Eigen::Vector3f( 0,   0,   1);
            auto v = Eigen::Vector3f( 0,   1,   0);
            auto w = Eigen::Vector3f(-1,   0,   0);

            auto s = e + uu*u + vv*v - dist*w;

            auto p = e;
            auto d = s - e;

            auto ray = Ray(p, d);

            auto triangles = kd_intersect(ray, kd_tree, 0, mt);

            auto scene = Scene(triangles, light);

            auto hit = scene.intersect(ray);
            if (hit)
                buffer[i*NY + j] = scene.shade(ray, *hit, 2, shadows, true).correct(2.2f);
            
            #if !defined(USE_OPENGL)
                printf("Rendering complete for pixel (%3d, %3d)\r", i, j);
            #endif
        }
    }
    printf("\n");

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        glutCreateWindow(shadows ? "Part 2 (with shadows)" : "Part 2 (without shadows)");
        glutDisplayFunc(gl_display);
        glutKeyboardFunc(gl_keyboard);
        glutMainLoop();
    #else
        // Write buffer to image file
        const char* path = shadows ? "images/part2b.ppm" : "images/part2a.ppm";
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