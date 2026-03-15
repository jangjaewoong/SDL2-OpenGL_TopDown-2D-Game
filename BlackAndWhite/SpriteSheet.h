#ifndef SPRITESHEET_CLASS_H
#define SPRITESHEET_CLASS_H
#include <glm/glm.hpp>
#include <vector>
#include "Texture2D.h"
struct UVRect
{
	glm::vec2 offset; // UV 시작점
	glm::vec2 scale; // UV 크기

};
class SpriteSheet
{
public:
	Texture2D texture;
	std::vector<UVRect> frames;
	SpriteSheet() {}

	SpriteSheet(Texture2D texture, int cols, int rows);

	const UVRect& GetFrame(int index) const;
};

#endif