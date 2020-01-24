#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>

#include "VertexAttribute.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();

	void Unbind();

private:
	unsigned int ID;
	std::vector<VertexAttribute> vertexAttributes;
	unsigned int vertexStride;							// Number of components for each vertex
	ElementBuffer EBO;
};

#endif // !VERTEXARRAY_H

