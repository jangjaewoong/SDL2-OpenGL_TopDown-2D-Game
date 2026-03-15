#ifndef SPRITERENDERER_CLASS_H
#define SPRITERENDERER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"
class SpriteRenderer
{
public:
	SpriteRenderer(Shader &shader, Camera* camera);
	~SpriteRenderer();

	void DrawSprite(Texture2D& texture, glm::vec2 position,
		glm::vec2 size, float rotate = 0.0f, glm::vec3 color = {1.0f, 1.0f, 1.0f},
		glm::vec2 uvOffset = { 0.0f,0.0f }, glm::vec2 uvScale = { 1.0f,1.0f } );
private:
	std::vector<float> vertices;
	Shader shader;
	Camera* camera;
	unsigned int SpriteVAO;
	void initRenderData();
};
#endif // !CLASS_SPRITERENDERER_H
