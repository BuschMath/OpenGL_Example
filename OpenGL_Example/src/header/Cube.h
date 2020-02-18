#ifndef CUBE_H
#define CUBE_H

#include "Texture.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "VertexBuffer.h"

#include <glad/glad.h>

enum class CubeType{
	BASIC, TEXTURE, NORM_BASIC, NORM_TEXTURE
};

class Cube
{
public:
	Cube();
	Cube(CubeType type);
	~Cube();

	void Bind();
	void Unbind();

	void VBO_Bind();
	void VBO_Unbind();

	void Draw();

private:
	VertexArray VAO;
	VertexBuffer VBO;
	VertexAttribute cubeLocation;
	VertexAttribute textureLocation;
	VertexAttribute normalLocation;
	float* vertices;
	unsigned int* indices;
	DrawType drawType;
	CubeType cubeType;

	unsigned int noVertices = 80;
	const unsigned int noIndices = 36;
	unsigned int numberOfDataPerVertex = 5;

	void TexCubeSetup();
	void NormTexCubeSetup();
	void BasicCubeSetup();
	void NormBasicCubeSetup();
};

#endif // !CUBE_H

