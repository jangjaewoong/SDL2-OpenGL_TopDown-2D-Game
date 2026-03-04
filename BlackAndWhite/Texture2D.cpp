#include "Texture2D.h"

Texture2D::Texture2D(const char* texturePath)
{
	
	glGenTextures(1, &ID);// first argument means "how many textures we want to generate"
	glBindTexture(GL_TEXTURE_2D, ID); // binding texture object 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);
	// Generating Texture
	if (data)
	{
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB; // Apply for RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
void Texture2D::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::UnBind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &ID);
}