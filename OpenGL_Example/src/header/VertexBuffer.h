#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <vector>

enum class DrawType {
	STATIC, DYNAMIC, STREAM
};

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class VertexBuffer
{
public:
	// Constructor
	// Precondition: glad.h is available for use
	// Postcondition: Object is created and ID is set.
	VertexBuffer();

	// Destructor
	~VertexBuffer();

	// Set as active vertex buffer
	// Precondition: Object has been created and ID set.
	// Postcondition: Vertex buffer is set as active buffer.
	void Bind();

	// Deactivate vertex buffer
	// Precondition: Object has been created and ID set.
	// Postcondition: No vertex buffer is active.
	void Unbind();

	// Sends data to GPU under ID
	// Precondition: Object has been created and ID set.
	// Postcondition: Data sent to GPU and vertex buffer is deactivated.
	void SetVertices(float* vertices, int numberOfData, DrawType type);

	void SetVertices(std::vector<Vertex> vertices, DrawType type);

private:
	unsigned int ID;
};

#endif // VERTEXBUFFER_H

