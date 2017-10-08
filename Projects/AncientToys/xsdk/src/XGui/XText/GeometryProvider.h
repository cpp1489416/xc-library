#pragma once
#include <vector>
#include <DirectXMath.h>

class GeometryProvider
{
public:
    struct Vertex;
    struct MeshData;

    struct MeshData
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    struct Vertex
    {
        Vertex(float x, float y, float z) : position(x, y, z) {}
        DirectX::XMFLOAT3 position;
    };

public:
    GeometryProvider();
    ~GeometryProvider();

    void createCube();
    void createCylinder(MeshData &data, size_t countSlices);
};

