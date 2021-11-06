#include "transform.h"

transform::transform() {
	localPos = glm::vec3(0, 0, 0);
	localRot = glm::identity<glm::quat>();
	localScl = glm::vec3(1, 1, 1);
}

transform::transform(glm::vec3 pos, glm::quat rot, glm::vec3 scl)
{
	localPos = pos;
	localRot = rot;
	localScl = scl;
}

glm::mat4 transform::localMat() const {
	//combine scale, rotation, and transform in that order and return
	glm::mat4 transformMatrix;
	glm::mat4 tPos = glm::translate(glm::identity<glm::mat4>(),localPos);
	glm::mat4 tRot = glm::toMat4(localRot);
	glm::mat4 tScl = glm::translate(glm::identity<glm::mat4>(),localPos);
	transformMatrix = tPos * tRot * tScl;

	return transformMatrix;
}

void transform::setParent(transform* newParent)
{
	parent = newParent;
}

transform* transform::getParent() const
{
	return parent;
}

transform* transform::getChildAtIndex(size_t index) const
{
	return children[index];
}

void transform::addChild(transform* const child)
{
	children.push_back(child);
}

void transform::removeChild(transform* const child)
{
	//for(size_t)
}

