#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
class Camera {
public:
	glm::vec2 position;
	glm::vec2 screenSize;
	Camera( glm::vec2 screenSize, glm::vec2 position = { 0.0f,0.0f });
	glm::mat4 GetViewMatrix();
	void Follow(glm::vec2 target);
};


#endif
