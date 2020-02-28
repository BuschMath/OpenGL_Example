#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
	vertexStride = 0;
	numberOfIndices = 0;
	indices = NULL;
	type = DrawType::STATIC;
}

VertexArray::~VertexArray()
{
	Unbind();
}

void VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexAttribute(VertexAttribute attribute)
{
	vertexAttributes.push_back(attribute);
}

void VertexArray::SetIndices(unsigned int* indices_, unsigned int numberOfIndices_, DrawType type_)
{
	indices = indices_;
	numberOfIndices = numberOfIndices_;
	type = type_;
}

void VertexArray::SetVAO_EBO()
{
	Bind();

	for (unsigned int i = 0; i < vertexAttributes.size(); i++)
	{
		glVertexAttribPointer(vertexAttributes[i].GetID(), vertexAttributes[i].GetSize(), GL_FLOAT, GL_FALSE,
			vertexStride, (void*)(vertexAttributes[i].GetOffset()));
		glEnableVertexAttribArray(vertexAttributes[i].GetID());
	}

	EBO.Bind();
	EBO.SetIndices(indices, numberOfIndices, type);

	Unbind();
}
