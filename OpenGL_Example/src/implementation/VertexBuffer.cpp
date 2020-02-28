#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &ID);
}

VertexBuffer::~VertexBuffer()
{
	Unbind();
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetVertices(float* vertices, int numberOfData, DrawType type)
{
	Bind();

	if(type == DrawType::STATIC)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfData, vertices, GL_STATIC_DRAW);
	if(type == DrawType::DYNAMIC)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfData, vertices, GL_DYNAMIC_DRAW);
	if(type == DrawType::STREAM)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfData, vertices, GL_STREAM_DRAW);
	
	Unbind();
}

void VertexBuffer::SetVertices(std::vector<Vertex> vertices, DrawType type)
{
	Bind();

	if (type == DrawType::STATIC)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	if (type == DrawType::DYNAMIC)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
	if (type == DrawType::STREAM)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STREAM_DRAW);

	Unbind();
}
