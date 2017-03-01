#include "RotationState.h"
#include "MagicCube.h"
#include <glm/ext.hpp>
#include <cstdlib>
#include <ctime>

namespace
{
    const float PI = 3.14159f;
}

namespace MagicCubes
{
    RotationState RotationState::GetRandomRotationState(int countRows)
    {
        RotationState state;
        state.mFace = Face(rand() % 3);
        state.mClockwise = Clockwise::CCW; //rand() % 2 == 1 | 0 ? Clockwise::CCW : Clockwise::CW;
        state.mTimes = rand() % 3 + 1;
        // state.mLineIndex = 1;
        state.mLineIndex = rand() % countRows;
        return state;
    }
  
    glm::mat4 RotationState::GetRotationMatrix() const
    {
        // rotation i2s left handed !
        glm::mat4 ans(1.0f);
        int directionFlag = mClockwise == Clockwise::CCW ? 1 : -1;
        switch (mFace)
        {
        case Face::Front:
            ans = glm::rotate(ans, PI / 2.0f * mTimes, glm::vec3(0, 0, directionFlag));
         //   ans = glm::rotate(ans, PI / 2.0f * mTimes, glm::vec3(-directionFlag, 0, 0));
            
            break;
        case Face::Right:
            ans = glm::rotate(ans, PI / 2.0f * mTimes, glm::vec3(-directionFlag, 0, 0));
            break;
        case Face::Up:
            ans = glm::rotate(ans, PI / 2.0f * mTimes, glm::vec3(0, -directionFlag, 0));
            break;
        default:
            break;
        }

        return ans;
    }
}