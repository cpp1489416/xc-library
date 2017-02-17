#pragma once

#include <vector>

class MeshProvider
{
public:
    class Vertex
    {
        float mX;
        float mY;
        float mZ;
    };

    typedef std::vector<Vertex> MeshVertices;
    typedef std::vector<unsigned int> MeshIndices;

public:
    MeshProvider() {}

private:
    
};