#ifndef TEXTURE2D_CLASS_H
#define TEXTURE2D_CLASS_H

#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture2D {
public:
	unsigned int ID;
	int width, height, nrChannels;
	Texture2D(const char* texturePath);
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
	~Texture2D();
};

#endif
