#ifndef CUBE_H
#define CUBE_H

#include "Texture.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "VertexBuffer.h"

#include <glad/glad.h>

const unsigned int noVertices = 80;
const unsigned int noIndices = 36;
const unsigned int numberOfDataPerVertex = 5;

class Cube
{
public:
	Cube();
	~Cube();

	void Bind();
	void Unbind();

	void Draw();

private:
	VertexArray VAO;
	VertexBuffer VBO;
	VertexAttribute cubeLocation;
	VertexAttribute textureLocation;
	float* vertices;
	unsigned int* indices;
	DrawType type;
};

#endif // !CUBE_H

