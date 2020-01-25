#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

enum class WrapType
{
	REPEAT, MIRRORED_REPEAT, CLAMP_EDGE, CLAMP_BORDER
};

enum class FilterType
{
	LINEAR, NEAREST
};

enum class ImageType
{
	JPG, PNG
};

class Texture
{
public:
	Texture();
	Texture(std::string location, ImageType type, WrapType wrap, FilterType filter);

	~Texture();

	void Bind();
	void Unbind();

	unsigned int GetID() { return ID; };

	// Expects vector of four elements RGBA, only needed if CLAMP_BOARDER is set
	void SetBoarderColor(float* color);

private:
	unsigned int ID;
};

#endif // !TEXTURE_H
