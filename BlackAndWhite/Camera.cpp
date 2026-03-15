#include "Camera.h"

Camera::Camera( glm::vec2 screenSize, glm::vec2 position) : screenSize(screenSize), position(position) {}


glm::mat4 Camera::GetViewMatrix() 
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(screenSize.x / 2 - position.x,
		screenSize.y / 2 - position.y, 0.0f));
	return view;
}
void Camera::Follow(glm::vec2 target) {
	this->position = target;
}