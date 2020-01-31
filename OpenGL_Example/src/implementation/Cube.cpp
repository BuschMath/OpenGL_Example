#include "Cube.h"

Cube::Cube()
{
	vertices = new float[noVertices] {
		// Vertices				// Texture		// Ver
		// Back face
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		// 0
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		// 1
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		// 2
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		// 3
		// Front face
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		// 4
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		// 5
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		// 6
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		// 7
		// Left face
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		// 8
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		// 9
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		// 10
		// Right face
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		// 11
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		// 12
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		// 13
		 // Bottom face
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,		// 14
		// Top face
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f 		// 15
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
	
	type = DrawType::STATIC;
	VBO.SetVertices(vertices, noVertices, type);
	VBO.Bind();

	cubeLocation.SetID(0);
	cubeLocation.SetSize(3);
	cubeLocation.SetOffset(0);
	VAO.AddVertexAttribute(cubeLocation);

	textureLocation.SetID(1);
	textureLocation.SetSize(2);
	textureLocation.SetOffset(3);
	VAO.AddVertexAttribute(textureLocation);

	VAO.SetIndices(indices, noIndices, type);
	VAO.SetVertexStride(numberOfDataPerVertex);
	VAO.SetVAO_EBO();

	VAO.Unbind();
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

void Cube::Draw()
{
	VAO.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	VAO.Unbind();
}
