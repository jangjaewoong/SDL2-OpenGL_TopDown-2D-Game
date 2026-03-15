#ifndef CLASS_GAMEOBJECT_H
#define CLASS_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "SpriteSheet.h"
class GameObject
{
public:
	SpriteSheet* sheet = nullptr;
	float elapsedTime = 0.0f;
	int currentFrame = 0;
	float frameInterval = 0.15f; // 기본값
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	glm::vec2 uvOffset;
	glm::vec2 uvScale;
	float Rotation;

	Texture2D Sprite;
	Animator* animator = nullptr;
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 uvOffset = glm::vec2(0.0f,0.0f), glm::vec2 uvScale= glm::vec2(1.0f, 1.0f), glm::vec3 color= glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2 velocity= glm::vec2(0.0f, 0.0f));

	void Update(float dt);
	virtual void Draw(SpriteRenderer& renderer);
};
#endif