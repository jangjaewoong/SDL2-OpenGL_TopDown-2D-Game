#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(Texture2D texture, int cols, int rows) : texture(texture)
{
	float w = 1.0f / cols;
	float h = 1.0f / rows;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			this->frames.push_back({{ c * w, r * h }, { w,h }});
		}
	}
}

const UVRect& SpriteSheet::GetFrame(int index) const
{
	if (index >= frames.size())
	{
		std::cerr << "Out of Frames Array Range" << std::endl;
	}
	return frames[index];
}