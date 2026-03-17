#ifndef CLASS_TILE_H
#define CLASS_TILE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "SpriteSheet.h"
#include "GameObject.h"
class Tile : public GameObject {
	SpriteSheet* sheet = nullptr;
	float elapsedTime = 0.0f;
	int currentFrame = 0;
	float frameInterval = 0.15f; // 기본값
	bool isSolid;
};

#endif