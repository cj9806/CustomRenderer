#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "GLM/glm.hpp"
#include "GLM/gtx/quaternion.hpp"
class transform
{
public:
    glm::vec3 localPos;
    glm::quat localRot;
    glm::vec3 localScl;

public:
    transform();

    glm::mat4 localMat() const;
};

