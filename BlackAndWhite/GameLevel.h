#ifndef CLASS_GAMELEVEL_H
#define CLASS_GAMELEVEL_H

#include <vector>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <set>


#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"


class GameLevel {
public:

	std::vector<GameObject> Tiles;
	std::set<std::string> solidGIDs;
	std::string layerName;
	GameLevel() {};

	void Load(const char* file, int layerIndex, unsigned int TileSizeX, unsigned int TileSizeY);
	void Draw(SpriteRenderer& renderer, Camera* camera, glm::vec2 screenSize);
private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int TileSizeX, unsigned int TileSizeY);
};
#endif