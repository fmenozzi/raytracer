#ifndef KD_H_
#define KD_H_

#include "Mesh.h"
#include "SurfaceList.h"

#include <vector>

struct Ray;
struct Material;

struct AABB {
    Vector3 min, max;

    bool intersects(const Ray& ray) const;
};

struct KdNode {
    int nodeId;
    AABB boundingBox;
    int leftChildId;
    int rightChildId;
    int splitAxis;
    float splitPosition;
    bool isLeaf;
    std::vector<int> triIndex;
};

extern std::vector<KdNode> kd_tree;

bool kd_load(const char* fileName, std::vector<KdNode> &kdTree);
SurfaceList kd_intersect(const Ray& ray, const std::vector<KdNode>& kd_tree, int id, const Material& mt);

#endif
