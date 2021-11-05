#include "transform.h"

transform::transform() {
	localPos = glm::vec3(0, 0, 0);
	localRot = glm::quat(0, 0, 0, 0);
	localScl = glm::vec3(1, 1, 1);
}

glm::mat4 transform::localMat() const {
	//combine scale, rotation, and transform in that order and return
	glm::mat4 transformMatrix;
	glm::mat4 tPos = glm::translate(glm::identity<glm::mat4>(),localPos);
	glm::mat4 tRot = glm::toMat4(localRot);
	glm::mat4 tScl = glm::translate(glm::identity<glm::mat4>(),localPos);
	transformMatrix = tScl * tRot * tPos;

	return transformMatrix;
}
