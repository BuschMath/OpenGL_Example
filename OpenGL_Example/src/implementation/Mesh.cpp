#include "Mesh.h"
#include "VertexBuffer.h"
#include <string>
#include <iostream>

Mesh::Mesh()
{
	VAO = new VertexArray;
	VBO = new VertexBuffer;
	EBO = new ElementBuffer;
}

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> texs)
{
	VAO = new VertexArray;
	VBO = new VertexBuffer;
	EBO = new ElementBuffer;

	vertices = vert;
	indices = ind;
	textures = texs;

	setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (int i = 0; i < textures.size(); i++)
	{
		textures[i].Activate(i);

		std::string number;
		std::string name;

		switch (textures[i].GetTexType)
		{
		case TextureType::diffuse:	name = "texture_diffuse";
			number = std::to_string(diffuseNr++);
			break;

		case TextureType::specular:	name = "texture_specular"; 
			number = std::to_string(specularNr++);
			break;

		default:	std::cout << "ERROR::MESH::DRAW::TEXTURETYPE_FAILURE\n\n";
			break;
		}
		shader.SetFloat(("material." + name + number).c_str(), i);
		textures[i].Bind();
	}

	textures[0].Activate(0);

	VAO->Bind();
	VBO->Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	VBO->Unbind();
	VAO->Unbind();
}

void Mesh::setupMesh()
{
	VAO->Bind();
	VBO->Bind();

	VBO->SetVertices(vertices, DrawType::STATIC);
	EBO->SetIndices(&indices[0], indices.size(), DrawType::STATIC);

	VAO->SetVertexStride(sizeof(Vertex));

	VertexAttribute* posAtt = new VertexAttribute;
	posAtt->SetID(0);
	posAtt->SetOffset(0);
	posAtt->SetSize(3);
	VAO->AddVertexAttribute(*posAtt);

	VertexAttribute* norAtt = new VertexAttribute;
	norAtt->SetID(1);
	norAtt->SetOffset(offsetof(Vertex, Normal));
	norAtt->SetSize(3);
	VAO->AddVertexAttribute(*norAtt);

	VertexAttribute* texAtt = new VertexAttribute;
	texAtt->SetID(2);
	texAtt->SetOffset(offsetof(Vertex, TexCoords));
	texAtt->SetSize(2);
	VAO->AddVertexAttribute(*texAtt);

	VAO->Unbind();
}
