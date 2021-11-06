#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "GLM/glm.hpp"
#include "GLM/gtx/quaternion.hpp"

#include <vector>
class transform
{
public:
    glm::vec3 localPos;
    glm::quat localRot;
    glm::vec3 localScl;

public:
    //default constructor
    transform();
    //extra constructor accounting for custom position
    transform(glm::vec3 pos, glm::quat rot, glm::vec3 scl);

    glm::mat4 localMat() const;

    // get/set parent
    void setParent(transform* newParent);
    transform* getParent() const;

    // get children
    transform* getChildAtIndex(size_t index) const;
    size_t getChildCount() const;

    // get global model matrix
    glm::mat4 worldMat() const;

    // matrix used for converting transforming local-space coordinates to world-space
    glm::mat4 localToWorldMatrix() const;
    // matrix used for converting transforming world-space coordinates to local-space
    glm::mat4 worldToLocalMatrix() const;
private:
    transform *parent;
    std::vector<transform*> children;

    void addChild(transform* const child);
    void removeChild(transform* const child);
};

