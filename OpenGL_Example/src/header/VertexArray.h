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
	void SetVertexAttributes();
	void EnableVertexAttributes();

	void SetIndices(float* indices_, unsigned int numberOfIndices);

private:
	unsigned int ID;
	std::vector<VertexAttribute> vertexAttributes;
	unsigned int vertexStride;							// Number of components for each vertex
	ElementBuffer EBO;
	float* indices;
	unsigned int numberOfIndices;
};

#endif // !VERTEXARRAY_H

