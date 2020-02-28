#ifndef MESH_H
#define MESH_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <vector>

#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> texs);
	~Mesh();

	void Draw(Shader shader);

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	VertexArray* VAO;
	VertexBuffer* VBO;
	ElementBuffer* EBO;

	void setupMesh();
};

#endif // !MESH_H

