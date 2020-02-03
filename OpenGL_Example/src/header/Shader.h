#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class Shader
{
public:

	// Default constructor
	Shader();

	// Constructor reads and builds shaders
	// Precondition: Vertex and fragment shaders have been written in separate files and stored in path location
	// Postcondition: Both shaders have been read, compiled, and linked
	Shader(const char* vertexPath, const char* fragmentPath);

	// Destructor
	~Shader();

	// Set function for ID
	void SetID(unsigned int ID_) { ID = ID_; };
	// Get function for ID
	unsigned int GetID() { return ID; };

	// Activate shader
	// Precondition: The shaders have been read, compiled, and linked
	// Postcondition: The shader program has been bounded
	void Use();

	void SetClearColor(float r, float g, float b, float a);

	// Utiliity uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;

private:
	unsigned int ID;
};

#endif	// SHADER_H