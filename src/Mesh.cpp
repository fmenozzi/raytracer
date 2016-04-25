#include "Mesh.h"
#include "KD.h"
#include "Ray.h"

#include <cstring>
#include <cfloat>

#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include <Eigen/Dense>

std::vector<Vector3>         gPositions;
std::vector<Vector3>         gNormals;
std::vector<TriangleIndices> gTriangles;

void tokenize(char* string, std::vector<std::string>& tokens, const char* delimiter) {
    char* token = strtok(string, delimiter);
    while (token != NULL) {
        tokens.push_back(std::string(token));
        token = strtok(NULL, delimiter);
    }
}

int face_index(const char* string) {
    int length = strlen(string);
    char* copy = new char[length + 1];
    memset(copy, 0, length+1);
    strcpy(copy, string);

    std::vector<std::string> tokens;
    tokenize(copy, tokens, "/");
    delete[] copy;
    return atoi(tokens.front().c_str());
}

void mesh_load(std::string fileName) {
    std::ifstream fin(fileName.c_str());
    if (!fin.is_open()) {
        printf("ERROR: Unable to load mesh from %s!\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }

    float xmin =  FLT_MAX;
    float xmax = -FLT_MAX;
    float ymin =  FLT_MAX;
    float ymax = -FLT_MAX;
    float zmin =  FLT_MAX;
    float zmax = -FLT_MAX;

    while (true) {
        char line[1024] = {0};
        fin.getline(line, 1024);

        if (fin.eof())
            break;

        if (strlen(line) <= 1)
            continue;

        std::vector<std::string> tokens;
        tokenize(line, tokens, " ");

        if (tokens[0] == "v") {
            float x = atof(tokens[1].c_str());
            float y = atof(tokens[2].c_str());
            float z = atof(tokens[3].c_str());

            xmin = std::min(x, xmin);
            xmax = std::max(x, xmax);
            ymin = std::min(y, ymin);
            ymax = std::max(y, ymax);
            zmin = std::min(z, zmin);
            zmax = std::max(z, zmax);

            Vector3 position = {x, y, z};
            gPositions.push_back(position);
        } else if (tokens[0] == "vn") {
            float x = atof(tokens[1].c_str());
            float y = atof(tokens[2].c_str());
            float z = atof(tokens[3].c_str());
            Vector3 normal = {x, y, z};
            gNormals.push_back(normal);
        } else if (tokens[0] == "f") {
            unsigned int a = face_index(tokens[1].c_str());
            unsigned int b = face_index(tokens[2].c_str());
            unsigned int c = face_index(tokens[3].c_str());
            TriangleIndices triangle;
            triangle.indices[0] = a - 1;
            triangle.indices[1] = b - 1;
            triangle.indices[2] = c - 1;
            gTriangles.push_back(triangle);
        }
    }

    fin.close();
}
