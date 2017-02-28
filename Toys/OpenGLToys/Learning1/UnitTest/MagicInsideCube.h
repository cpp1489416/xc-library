#pragma once

#include "../CXCGL/Thing.h"
#include "../CXCGL/VertexArrayObject.h"

class MagicInsideCube : public Thing
{
public:
    enum class Color : int
    {
        White = 0, Green, Yellow, Blue, Red, Orange, Black,
    };

    enum class Face : int
    {
        Front = 0, Back, Left, Right, Up, Down,
    };

public:
    MagicInsideCube();

public:
    void SetFaceColor(Face face, Color color);
    VertexArrayObject * GetVertexArrayObject() { return &mVertexArrayObject; }

protected:
    void OnCreate() override;
    void OnChangeTechnique(Technique * technique) override {}
    void OnDraw() override;
    void OnDestroy() override {}

private:
    void SetColor(float * vertex, Color color);

private:
    Color mFaceColors[6];
    VertexArrayObject mVertexArrayObject = VertexArrayObject();
    Buffer mPositionArrayBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mColorArrayBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
};