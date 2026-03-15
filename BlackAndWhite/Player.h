#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "ResourceManager.h"
class Player : public GameObject
{
public:
	unsigned int currentFrame = 0;
	float moveSpeed = 300.0f;
	std::string lastDir = "down";
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void Update(float dt);

};


#endif