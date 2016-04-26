#include "KD.h"
#include "Ray.h"
#include "Material.h"
#include "Triangle.h"

#include <algorithm>

#include <Eigen/Dense>

std::vector<KdNode> kd_tree;

bool AABB::intersects(const Ray& ray) const {
    auto p = ray.p;
    auto d = ray.d;

    auto d_inv = Eigen::Vector3f(1.0f/d[0], 1.0f/d[1], 1.0f/d[2]);

    float mins[3] = {min.x, min.y, min.z};
    float maxs[3] = {max.x, max.y, max.z};

    float t1 = (mins[0] - p[0]) * d_inv[0];
    float t2 = (maxs[0] - p[0]) * d_inv[0];
 
    float tmin = std::min(t1, t2);
    float tmax = std::max(t1, t2);
 
    for (int i = 1; i < 3; ++i) {
        t1 = (mins[i] - p[i]) * d_inv[i];
        t2 = (maxs[i] - p[i]) * d_inv[i];
 
        tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
        tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));
    }
 
    return tmax > std::max(tmin, 0.0f);
}

bool kd_load(const char* fileName, std::vector<KdNode> &kdTree) {
    FILE* fp = fopen(fileName, "r+");
    if (!fp) {
        fprintf(stderr, "Could not load %s\n", fileName);
        return false;
    }
    char temp[256];
    int nodeId = -1;
    while (true) {
        *temp = '\0';
        nodeId++;
        int ignore = fscanf(fp, "%s{ ", temp);
        if (!ignore) {
            fprintf(stderr, "Something catastrophic went wrong\n");
            exit(EXIT_FAILURE);
        }
        if (strcmp(temp, "inner{") == 0) {
            KdNode kd;
            kd.nodeId = nodeId;
            kd.isLeaf = false;
            int ignore = fscanf(fp, "%f %f %f %f %f %f ; %d %d %d %f }", 
                                &kd.boundingBox.min.x, 
                                &kd.boundingBox.min.y, 
                                &kd.boundingBox.min.z, 
                                &kd.boundingBox.max.x, 
                                &kd.boundingBox.max.y, 
                                &kd.boundingBox.max.z, 
                                &kd.leftChildId, 
                                &kd.rightChildId, 
                                &kd.splitAxis, 
                                &kd.splitPosition);
            if (!ignore) {
                fprintf(stderr, "Something catastrophic went wrong\n");
                exit(EXIT_FAILURE);
            }
            kdTree.push_back(kd);
        } else if (strcmp(temp, "leaf{") == 0) {
            KdNode kd;
            kd.nodeId = nodeId;
            kd.isLeaf = true;
            int ignore = fscanf(fp, "%f %f %f %f %f %f ;", 
                                &kd.boundingBox.min.x, 
                                &kd.boundingBox.min.y, 
                                &kd.boundingBox.min.z, 
                                &kd.boundingBox.max.x, 
                                &kd.boundingBox.max.y, 
                                &kd.boundingBox.max.z);
            if (!ignore) {
                fprintf(stderr, "Something catastrophic went wrong\n");
                exit(EXIT_FAILURE);
            }
            char token[256];
            while (true) {
                int ignore = fscanf(fp, " %s", token);
                if (!ignore) {
                    fprintf(stderr, "Something catastrophic went wrong\n");
                    exit(EXIT_FAILURE);
                }
                if (strcmp(token, "}") == 0)
                    break;
                int triIndex = atoi(token);
                kd.triIndex.push_back(triIndex);
            }
            kdTree.push_back(kd);
        } else {
            break;
        }
    }
    return true;
}

SurfaceList kd_intersect(const Ray& ray, const std::vector<KdNode>& kd_tree, int id, const Material& mt) {
    auto node = kd_tree[id];
    if (node.isLeaf) {
        // Construct all leaf triangles
        SurfaceList leaves;
        for (int i : node.triIndex) {
            int k0 = gTriangles[i].indices[0];
            int k1 = gTriangles[i].indices[1];
            int k2 = gTriangles[i].indices[2];

            auto a = Eigen::Vector3f(gPositions[k0].x, gPositions[k0].y, gPositions[k0].z);
            auto b = Eigen::Vector3f(gPositions[k1].x, gPositions[k1].y, gPositions[k1].z);
            auto c = Eigen::Vector3f(gPositions[k2].x, gPositions[k2].y, gPositions[k2].z);

            auto n = ((b-a).cross(c-a)).normalized();

            auto triangle1 = std::unique_ptr<Triangle>(new Triangle(a,b,c,n,mt));
            auto triangle2 = std::unique_ptr<Triangle>(new Triangle(c,b,a,-n,mt));

            leaves.add(std::move(triangle1));
            leaves.add(std::move(triangle2));
        }
        return leaves;
    } else {
        SurfaceList surfaces;

        // Recurse on children whose bounding boxes intersect ray
        auto left_node  = kd_tree[node.leftChildId];
        auto right_node = kd_tree[node.rightChildId];
        if (left_node.boundingBox.intersects(ray)) {
            auto left_triangles = kd_intersect(ray, kd_tree, node.leftChildId, mt);
            surfaces.add(left_triangles);
        }
        if (right_node.boundingBox.intersects(ray)) {
            auto right_triangles = kd_intersect(ray, kd_tree, node.rightChildId, mt);
            surfaces.add(right_triangles);
        }

        return surfaces;
    }
}
