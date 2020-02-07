#include "Cube.h"

#include <iostream>

Cube::Cube()
{
	TexCubeSetup();
}

Cube::Cube(CubeType type)
{
	cubeType = type;

	if (cubeType == CubeType::BASIC)
		BasicCubeSetup();
	else if (cubeType == CubeType::TEXTURE)
		TexCubeSetup();
	else if (cubeType == CubeType::NORM_BASIC)
		NormBasicCubeSetup();
	else
		std::cout << "ERROR::CUBE::CONSTRUCTOR::CUBETYPEFAILURE\n";
}

Cube::~Cube()
{
	delete vertices;
	delete indices;
}

void Cube::Bind()
{
	VAO.Bind();
}

void Cube::Unbind()
{
	VAO.Unbind();
}

void Cube::VBO_Bind()
{
	VBO.Bind();
}

void Cube::VBO_Unbind()
{
	VBO.Unbind();
}

void Cube::Draw()
{
	Bind();
	glDrawElements(GL_TRIANGLES, noIndices, GL_UNSIGNED_INT, 0);
	Unbind();
}

void Cube::TexCubeSetup()
{
	cubeType = CubeType::TEXTURE;
	noVertices = 80;
	numberOfDataPerVertex = 5;

	vertices = new float[noVertices] {
		// Vertices				// Texture		// Ver
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,		// 0
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,		// 1
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,		// 2
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,		// 3
		// Front face
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,		// 4
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,		// 5
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,		// 6
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,		// 7
		// Left face
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,		// 8
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,		// 9
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,		// 10
		// Right face
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,		// 11
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,		// 12
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,		// 13
		// Bottom face
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,		// 14
		   // Top face
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f 		// 15
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
			10, 4, 8,			// Second triangle
			// Right face
			11, 2, 12,			// First triangle
			12, 13, 11,			// Second triangle
			// Bottom face
			10, 14, 5,			// First triangle
			5, 4, 10,			// Second triangle
			// Top face
			3, 2, 11,			// First triangle
			11, 15, 3			// Second triangle
	};

	VAO.Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO.AddVertexAttribute(cubeLocation);

	textureLocation.SetID(1);
	textureLocation.SetSize(2);
	textureLocation.SetOffset(3);
	VAO.AddVertexAttribute(textureLocation);

	VAO.SetIndices(indices, noIndices, drawType);
	VAO.SetVertexStride(numberOfDataPerVertex);
	VAO.SetVAO_EBO();

	VAO.Unbind();
}

void Cube::BasicCubeSetup()
{
	cubeType = CubeType::BASIC;
	noVertices = 48;
	numberOfDataPerVertex = 3;

	vertices = new float[noVertices] {
		// Vertices				// Texture		// Ver
		// Back face
		-0.5f, -0.5f, -0.5f,		// 0
		 0.5f, -0.5f, -0.5f,		// 1
		 0.5f,  0.5f, -0.5f,		// 2
		-0.5f,  0.5f, -0.5f,		// 3
		// Front face
		-0.5f, -0.5f,  0.5f,		// 4
		 0.5f, -0.5f,  0.5f,		// 5
		 0.5f,  0.5f,  0.5f,		// 6
		-0.5f,  0.5f,  0.5f,		// 7
		// Left face
		-0.5f,  0.5f,  0.5f,		// 8
		-0.5f,  0.5f, -0.5f,		// 9
		-0.5f, -0.5f, -0.5f,		// 10
		// Right face
		 0.5f,  0.5f,  0.5f,		// 11
		 0.5f, -0.5f, -0.5f,		// 12
		 0.5f, -0.5f,  0.5f,		// 13
		   // Bottom face
		 0.5f, -0.5f, -0.5f,		// 14
		  // Top face
		-0.5f,  0.5f,  0.5f			// 15
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
		10, 4, 8,			// Second triangle
		// Right face
		11, 2, 12,			// First triangle
		12, 13, 11,			// Second triangle
		// Bottom face
		10, 14, 5,			// First triangle
		5, 4, 10,			// Second triangle
		// Top face
		3, 2, 11,			// First triangle
		11, 15, 3			// Second triangle
	};

	VAO.Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO.AddVertexAttribute(cubeLocation);

	VAO.SetIndices(indices, noIndices, drawType);
	VAO.SetVertexStride(numberOfDataPerVertex);
	VAO.SetVAO_EBO();

	VAO.Unbind();
}

void Cube::NormBasicCubeSetup()
{
	cubeType = CubeType::NORM_BASIC;
	noVertices = 144;
	numberOfDataPerVertex = 6;

	vertices = new float[noVertices] {
		// Vertices				// Norm vec
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f
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

	VAO.Bind();

	drawType = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, drawType);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO.AddVertexAttribute(cubeLocation);

	normalLocation.SetID(1);
	normalLocation.SetSize(3);
	normalLocation.SetOffset(3);
	VAO.AddVertexAttribute(normalLocation);

	VAO.SetIndices(indices, noIndices, drawType);
	VAO.SetVertexStride(numberOfDataPerVertex);
	VAO.SetVAO_EBO();

	VAO.Unbind();
}
