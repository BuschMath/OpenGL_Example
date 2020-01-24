#include "ElementBuffer.h"

ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &ID);
}

ElementBuffer::~ElementBuffer()
{
	Unbind();
}

void ElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::SetIndices(float* indices, int numberOfIndices, DrawType type)
{
	if(type == DrawType::STATIC)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numberOfIndices, indices, GL_STATIC_DRAW);
	if (type == DrawType::DYNAMIC)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numberOfIndices, indices, GL_DYNAMIC_DRAW);
	if (type == DrawType::STREAM)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numberOfIndices, indices, GL_STREAM_DRAW);
}
