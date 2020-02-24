#ifndef CUBE_H
#define CUBE_H

#include "Texture.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "VertexBuffer.h"

#include <glad/glad.h>
#include <vector>

using namespace std;

enum class CubeType{
	BASIC, TEXTURE, NORM_BASIC, NORM_TEXTURE
};

class Cube
{
public:
	Cube();
	Cube(CubeType type);
	~Cube();

	void Bind(int cubeNo);
	void Unbind();

	void VBO_Bind();
	void VBO_Unbind();

	void AddCube(CubeType cubeType);

	void Draw(int cubeNo);

private:
	vector<VertexArray> VAO;
	VertexBuffer VBO;
	VertexAttribute cubeLocation;
	VertexAttribute textureLocation;
	VertexAttribute normalLocation;
	float* vertices;
	unsigned int* indices;
	DrawType drawType;
	CubeType cubeType;
	int numberOfCubes = 0;

	unsigned int noVertices = 192;
	const unsigned int noIndices = 36;
	unsigned int numberOfDataPerVertex = 8;

	void TexCubeSetup();
	void NormTexCubeSetup();
	void BasicCubeSetup();
	void NormBasicCubeSetup();
};

#endif // !CUBE_H

