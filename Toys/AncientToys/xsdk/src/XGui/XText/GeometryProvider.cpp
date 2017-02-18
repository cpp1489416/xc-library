#include "GeometryProvider.h"
#include <cmath>

using namespace std;
using namespace DirectX;

GeometryProvider::GeometryProvider()
{
}


GeometryProvider::~GeometryProvider()
{
}

void GeometryProvider::createCube()
{
}

void GeometryProvider::createCylinder(MeshData & data, size_t countSlices)
{
    data.vertices.clear();
    data.indices.clear();
    
    data.vertices.push_back(Vertex(0.0f, 0.0f, -1.0f));
    size_t centerTop = 0;
    for (int i = 0; i < countSlices; i++)
    {
        float x = cos(XM_2PI * (i / (float)countSlices));
        float y = sin(XM_2PI * (i / (float)countSlices));
        data.vertices.push_back(Vertex(x, y, -1));
    }

    data.vertices.push_back(Vertex(0.0f, 0.0f, 1.0f));
    size_t centerBottom = data.vertices.size() - 1;
    for (int i = 0; i < countSlices; i++)
    {
        float x = cos(XM_2PI * (i / (float)countSlices));
        float y = sin(XM_2PI * (i / (float)countSlices));
        data.vertices.push_back(Vertex(x, y, 1));
    }

    for (size_t i = 1; i < countSlices; i++)
    {
        data.indices.push_back(centerTop);
        data.indices.push_back(centerTop + i);
        data.indices.push_back(centerTop + i + 1);
    }

    for (size_t i = 1; i < countSlices; i++)
    {
        data.indices.push_back(centerBottom);
        data.indices.push_back(centerBottom + i);
        data.indices.push_back(centerBottom + (i + 1) % countSlices + 1);
    }

    for (size_t i = 1; i < countSlices; i++)
    {
        data.indices.push_back(centerTop + i);
        data.indices.push_back(centerBottom + i);
        data.indices.push_back(centerBottom + i + 1);

        data.indices.push_back(centerBottom + i + 1);
        data.indices.push_back(centerTop + i);
        data.indices.push_back(centerTop + i + 1);
    }
    
    data.indices.push_back(centerTop + countSlices);
    data.indices.push_back(centerBottom + countSlices);
    data.indices.push_back(centerBottom + 1);

    data.indices.push_back(centerBottom + 1);
    data.indices.push_back(centerTop + countSlices);
    data.indices.push_back(centerTop + 1);
    
}
