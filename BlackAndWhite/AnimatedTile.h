#ifndef CLASS_ANIMATEDTILE_H
#define CLASS_ANIMATEDTILE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "ResourceManager.h"

class AnimatedTile : public GameObject
{
public:
	Animator* animator;
	AnimatedTile()
};


#endif