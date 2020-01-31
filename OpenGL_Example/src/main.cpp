// Vendor headers ********************************
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

// Local headers ********************************
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "VertexAttribute.h"
#include "App.h"
#include "Texture.h"
#include "Window.h"
#include "Cube.h"

// Global constants ********************************
const int windowWidth = 800;
const int windowHeight = 600;

// Global variables ********************************

// Helper function prototypes ********************************

int main()
{
	// ************************************************
	// Initialize GLFW
	// ************************************************
	App app((int)windowWidth, (int)windowHeight, "Title", glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

	// Set mouse input and callback
	app.SetInputMode(InputModeType::CURSOR, InputValueType::DISABLED);

	// ************************************************
	// Load and generate texture
	// ************************************************
	Texture texture0("res/container.jpg", ImageType::JPG, WrapType::REPEAT, FilterType::LINEAR);
	Texture texture1("res/awesomeface.png", ImageType::PNG, WrapType::REPEAT, FilterType::LINEAR);

	// ************************************************
	// Set rectangle vertices
	// ************************************************
	// Set vertices of a triangle in normalized device coordinates
	Cube c;
	
	// ************************************************
	// Shader program
	// ************************************************
	Shader shader("vertexShader.shader", "fragmentShader.shader");

	// Activate shader program
	shader.Use();

	// Set uniforms
	shader.SetInt("texture0", 0);
	shader.SetInt("texture1", 1);

	// ************************************************
	// Create Model View Projection matrix
	// ************************************************
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// ************************************************
	// Render loop
	// ************************************************
	while (!glfwWindowShouldClose(app.GetWindow()))
	{
		// Input
		app.ProcessInput();
		app.HandleMouse();

		// Rendering
		app.UpdateFrameTime();

		// Set clear color state defined as Red, Blue, Green, Alpha
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		// Color the buffer to match clear color state
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		// ************************************************
		// Send MVP matrix uniforms
		// ************************************************
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			if(i % 3 == 0)
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			int modelLoc = glGetUniformLocation(shader.GetID(), "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());
			int viewLoc = glGetUniformLocation(shader.GetID(), "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);
			int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0.GetID());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1.GetID());
			
			c.Draw();
		}

		app.BufferSwapAndPoll();
	}

	return 0;
}
