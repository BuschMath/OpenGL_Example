#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>

#include "VertexAttribute.h"
#include "ElementBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();

	void Unbind();

	void SetVertexStride(unsigned int vertexStride_) { vertexStride = vertexStride_; };
	unsigned int GetVertexStride() { return vertexStride; };

	void AddVertexAttribute(VertexAttribute attribute);

	void SetIndices(unsigned int* indices_, unsigned int numberOfIndices_, DrawType type_);

	void SetVAO_EBO();

private:
	unsigned int ID;
	std::vector<VertexAttribute> vertexAttributes;
	unsigned int vertexStride;							// Number of components for each vertex
	ElementBuffer EBO;
	DrawType type;
	unsigned int* indices;
	unsigned int numberOfIndices;
};

#endif // !VERTEXARRAY_H
