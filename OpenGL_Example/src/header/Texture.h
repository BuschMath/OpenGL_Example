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

enum class TextureType
{
	diffuse, specular
};

class Texture
{
public:
	Texture();
	Texture(std::string location, ImageType type, WrapType wrap, FilterType filter, TextureType textureType);

	~Texture();

	void Bind();
	void Unbind();

	void Activate(unsigned int i);

	unsigned int GetID() { return ID; };
	TextureType GetTexType() { return texType; };

	// Expects vector of four elements RGBA, only needed if CLAMP_BOARDER is set
	void SetBoarderColor(float* color);

private:
	unsigned int ID;
	TextureType texType;
};

#endif // !TEXTURE_H
