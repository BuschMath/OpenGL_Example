#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

class VertexAttribute
{
public:
	VertexAttribute();
	~VertexAttribute();

	void SetID(unsigned int ID_) { ID = ID_; };
	unsigned int GetID() { return ID; };

	void SetSize(unsigned int size_) { size = size_; };
	unsigned int GetSize() { return size; };

	void SetOffset(unsigned int offset_) { offset = offset_; };
	unsigned int GetOffset() { return offset; };

private:
	unsigned int ID;
	unsigned int size;		// Numbers of componends per vertex
	unsigned int offset;	// Number of componends from the beginning of each vertex to the attribute data
};

VertexAttribute::VertexAttribute()
{
	ID = 999999;
	size = 999999;
	offset = 999999;
}

VertexAttribute::~VertexAttribute()
{
}

#endif // !VERTEXATTRIBUTE_H

