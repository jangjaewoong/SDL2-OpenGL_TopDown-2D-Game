#ifndef CLASS_ANIMATOR_H
#define CLASS_ANIMATOR_H

#include <iostream>
#include <glad/glad.h>
#include <unordered_map>
#include "SpriteSheet.h"

class Animator {
public :
	std::unordered_map<std::string, SpriteSheet> sheets;
	std::string currentAnim;
	int currentFrame = 0;
	float elapsedTime = 0.0f;
	float frameInterval = 0.1f;

	void AddSheet(const std::string& name, SpriteSheet sheet);
	void Play(const std::string& name);
	void Update(float dt);

	const UVRect& GetCurrentUV() {
		return sheets[currentAnim].GetFrame(currentFrame);
	}

	Texture2D& GetCurrentTexture() {
		return sheets[currentAnim].texture;
	}

};

#endif