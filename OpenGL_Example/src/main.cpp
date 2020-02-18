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
	App app((int)windowWidth, (int)windowHeight, "Title", glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

	// Set mouse input and callback
	app.SetInputMode(InputModeType::CURSOR, InputValueType::DISABLED);


	// ************************************************
	// Set rectangle vertices
	// ************************************************
	// Set vertices of a triangle in normalized device coordinates
	Cube c(CubeType::NORM_BASIC);
	Cube light(CubeType::BASIC);

	Texture texBox("res/container2.png", ImageType::PNG, WrapType::REPEAT, FilterType::LINEAR);
	
	// ************************************************
	// Shader program
	// ************************************************
	Shader shader("vsMVP_Lighting.shader", "fsLight.shader");
	Shader lightingShader("vsMVP_woTexture.shader", "fsLightSource.shader");
	lightingShader.Use();

	// Activate shader program
	shader.Use();

	// Set uniforms
	shader.SetInt("material.diffuse", 0);

	// ************************************************
	// Create Model View Projection matrix
	// ************************************************
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
	glm::vec3 modelPos(0.0f, 0.0f, 0.0f);

	shader.SetVec3("light.position", lightPos);
	shader.SetVec3("viewPos", app.GetCamPos());

	shader.SetVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetFloat("material.shininess", 32.0f);

	shader.SetVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

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

		shader.SetClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		shader.Use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, modelPos);
		shader.SetMat4("model", model);

		view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());
		shader.SetMat4("view", view);

		projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);
		shader.SetMat4("projection", projection);

		texBox.Activate(0);
		texBox.Bind();

		c.Draw();


		// ************************************************
		// light
		// ************************************************
		lightingShader.Use();

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightingShader.SetMat4("model", model);

		view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());
		lightingShader.SetMat4("view", view);

		projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);
		lightingShader.SetMat4("projection", projection);
		
		light.Draw();

		app.BufferSwapAndPoll();
	}

	return 0;
}
