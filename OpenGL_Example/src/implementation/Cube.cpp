#include "Cube.h"

#include <iostream>

Cube::Cube()
{
	TexCubeSetup();
}

Cube::Cube(CubeType type)
{
	cubeType = type;
	drawType = DrawType::STATIC;
	vertices = new float[noVertices] {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	indices = new unsigned int[noIndices] {
		// Back face
		0, 1, 2,			// First triangle
			2, 3, 0,			// Second triangle
			// Front face
			4, 5, 6,			// First triangle
			6, 7, 4,			// Second triangle
			// Left face
			8, 9, 10,			// First triangle
			10, 11, 8,			// Second triangle
			// Right face
			12, 13, 14,			// First triangle
			14, 15, 12,			// Second triangle
			// Bottom face
			16, 17, 18,			// First triangle
			18, 19, 16,			// Second triangle
			// Top face
			20, 21, 22,			// First triangle
			22, 23, 20			// Second triangle
	};

	AddCube(cubeType);
}

Cube::~Cube()
{
	delete vertices;
	delete indices;
}

void Cube::Bind(int cubeNo)
{
	VAO[cubeNo].Bind();
}

void Cube::Unbind()
{
	VAO[0].Unbind();
}

void Cube::VBO_Bind()
{
	VBO.Bind();
}

void Cube::VBO_Unbind()
{
	VBO.Unbind();
}

void Cube::AddCube(CubeType cubeType)
{
	if (cubeType == CubeType::BASIC)
		BasicCubeSetup();
	else if (cubeType == CubeType::TEXTURE)
		TexCubeSetup();
	else if (cubeType == CubeType::NORM_BASIC)
		NormBasicCubeSetup();
	else if (cubeType == CubeType::NORM_TEXTURE)
		NormTexCubeSetup();
	else
		std::cout << "ERROR::CUBE::CONSTRUCTOR::CUBETYPEFAILURE\n";
}

void Cube::Draw(int cubeNo)
{
	Bind(cubeNo);
	glDrawElements(GL_TRIANGLES, noIndices, GL_UNSIGNED_INT, 0);
	Unbind();
}

void Cube::TexCubeSetup()
{
	cubeType = CubeType::TEXTURE;

	VertexArray* tempArray = new VertexArray;
	VAO.push_back(*tempArray);

	VAO[numberOfCubes].Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO[numberOfCubes].AddVertexAttribute(cubeLocation);

	textureLocation.SetID(1);
	textureLocation.SetSize(2);
	textureLocation.SetOffset(6);
	VAO[numberOfCubes].AddVertexAttribute(textureLocation);

	VAO[numberOfCubes].SetIndices(indices, noIndices, drawType);
	VAO[numberOfCubes].SetVertexStride(numberOfDataPerVertex);
	VAO[numberOfCubes].SetVAO_EBO();

	VAO[numberOfCubes].Unbind();

	numberOfCubes++;
}

void Cube::NormTexCubeSetup()
{
	cubeType = CubeType::NORM_TEXTURE;

	VertexArray* tempArray = new VertexArray;
	VAO.push_back(*tempArray);

	VAO[numberOfCubes].Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO[numberOfCubes].AddVertexAttribute(cubeLocation);

	normalLocation.SetID(1);
	normalLocation.SetSize(3);
	normalLocation.SetOffset(3);
	VAO[numberOfCubes].AddVertexAttribute(normalLocation);

	textureLocation.SetID(2);
	textureLocation.SetSize(2);
	textureLocation.SetOffset(6);
	VAO[numberOfCubes].AddVertexAttribute(textureLocation);

	VAO[numberOfCubes].SetIndices(indices, noIndices, drawType);
	VAO[numberOfCubes].SetVertexStride(numberOfDataPerVertex);
	VAO[numberOfCubes].SetVAO_EBO();

	VAO[numberOfCubes].Unbind();

	numberOfCubes++;
}

void Cube::BasicCubeSetup()
{
	cubeType = CubeType::BASIC;

	VertexArray* tempArray = new VertexArray;
	VAO.push_back(*tempArray);

	VAO[numberOfCubes].Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO[numberOfCubes].AddVertexAttribute(cubeLocation);

	VAO[numberOfCubes].SetIndices(indices, noIndices, drawType);
	VAO[numberOfCubes].SetVertexStride(numberOfDataPerVertex);
	VAO[numberOfCubes].SetVAO_EBO();

	VAO[numberOfCubes].Unbind();

	numberOfCubes++;
}

void Cube::NormBasicCubeSetup()
{
	cubeType = CubeType::NORM_BASIC;

	VertexArray* tempArray = new VertexArray;
	VAO.push_back(*tempArray);

	VAO[numberOfCubes].Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO[numberOfCubes].AddVertexAttribute(cubeLocation);

	normalLocation.SetID(1);
	normalLocation.SetSize(3);
	normalLocation.SetOffset(3);
	VAO[numberOfCubes].AddVertexAttribute(normalLocation);

	VAO[numberOfCubes].SetIndices(indices, noIndices, drawType);
	VAO[numberOfCubes].SetVertexStride(numberOfDataPerVertex);
	VAO[numberOfCubes].SetVAO_EBO();

	VAO[numberOfCubes].Unbind();

	numberOfCubes++;
}
