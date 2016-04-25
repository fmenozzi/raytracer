#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <string>

struct Vector3 {
    float x, y, z;
};

struct TriangleIndices {
    unsigned int indices[3];
};

extern std::vector<Vector3>         gPositions;
extern std::vector<Vector3>         gNormals;
extern std::vector<TriangleIndices> gTriangles;

void tokenize(char* string, std::vector<std::string>& tokens, const char* delimiter);
int face_index(const char* string);
void mesh_load(std::string fileName);

#endif
