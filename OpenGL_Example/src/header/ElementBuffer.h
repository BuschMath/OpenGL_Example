#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include "VertexBuffer.h"		// Included for DrawType

class ElementBuffer
{
public:
	ElementBuffer();
	~ElementBuffer();

	void Bind();
	void Unbind();

	void SetIndices(unsigned int* indices, int numberOfIndices, DrawType type);

private:
	unsigned int ID;
};

#endif // !ELEMENTBUFFER_H

