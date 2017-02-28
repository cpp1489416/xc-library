#pragma once

#include "MagicCubeEnums.h"
#include "../CXCGL/Thing.h"
#include "../CXCGL/VertexArrayObject.h"
#include <glm/matrix.hpp>

namespace MagicCube
{
    class RotationState;

    class MagicInsideCube : public Thing
    {
    public:
        MagicInsideCube();

    public:
        void SetFaceColor(Direction face, Color color);
        VertexArrayObject * GetVertexArrayObject() { return &mVertexArrayObject; }
        glm::mat4 GetRotationMatrix() const { return mRotationMatrix; }
        void SetRotationMatrix(const glm::mat4 rotationMatrix) { mRotationMatrix = rotationMatrix; }

    public:
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
        glm::mat4 mRotationMatrix = glm::mat4(1.0f);
    };
}