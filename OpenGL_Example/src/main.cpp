// Vendor headers ********************************
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <vector>

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
const int windowWidth = 1600;
const int windowHeight = 1200;

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
	Cube c(CubeType::NORM_TEXTURE);

	c.AddCube(CubeType::BASIC);

	Texture texBox("res/container2.png", ImageType::PNG, WrapType::REPEAT, FilterType::LINEAR);
	Texture specMap("res/container2_specular.png", ImageType::PNG, WrapType::REPEAT, FilterType::LINEAR);
	
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
	shader.SetInt("material.specular", 1);

	// ************************************************
	// Create Model View Projection matrix
	// ************************************************
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 pointLightPos[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	
	glm::vec3 modelPos[] = {
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

	shader.SetVec3("pointLights[0].position", pointLightPos[0]);
	shader.SetVec3("pointLights[1].position", pointLightPos[1]);
	shader.SetVec3("pointLights[2].position", pointLightPos[2]);
	shader.SetVec3("pointLights[3].position", pointLightPos[3]);

	shader.SetVec3("viewPos", app.GetCamPos());

	shader.SetFloat("material.shininess", 32.0f);

	shader.SetVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader.SetVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.SetVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.SetVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	shader.SetVec3("pointLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.SetVec3("pointLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetFloat("pointLights[0].constant", 1.0f);
	shader.SetFloat("pointLights[0].linear", 0.09f);
	shader.SetFloat("pointLights[0].quadratic", 0.032f);

	shader.SetVec3("pointLights[1].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.SetVec3("pointLights[1].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetFloat("pointLights[1].constant", 1.0f);
	shader.SetFloat("pointLights[1].linear", 0.09f);
	shader.SetFloat("pointLights[1].quadratic", 0.032f);

	shader.SetVec3("pointLights[2].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.SetVec3("pointLights[2].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetFloat("pointLights[2].constant", 1.0f);
	shader.SetFloat("pointLights[2].linear", 0.09f);
	shader.SetFloat("pointLights[2].quadratic", 0.032f);

	shader.SetVec3("pointLights[3].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.SetVec3("pointLights[3].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetFloat("pointLights[3].constant", 1.0f);
	shader.SetFloat("pointLights[3].linear", 0.09f);
	shader.SetFloat("pointLights[3].quadratic", 0.032f);

	shader.SetVec3("spotLight.position", app.GetCamPos());
	shader.SetVec3("spotLight.direction", app.GetCamFront());
	shader.SetVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.SetVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetFloat("spotLight.constant", 1.0f);
	shader.SetFloat("spotLight.linear", 0.09f);
	shader.SetFloat("spotLight.quadratic", 0.032f);
	shader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

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

		shader.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		shader.Use();

		shader.SetVec3("spotLight.position", app.GetCamPos());
		shader.SetVec3("spotLight.direction", app.GetCamFront());

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, modelPos[i]);
			model = glm::rotate(model, glm::radians(10 * (float)glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetMat4("model", model);

			view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());
			shader.SetMat4("view", view);

			projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);
			shader.SetMat4("projection", projection);

			texBox.Activate(0);
			texBox.Bind();

			specMap.Activate(1);
			specMap.Bind();

			c.Draw(0);
		}

		// ************************************************
		// light
		// ************************************************
		lightingShader.Use();
		for (int i = 0; i < 4; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPos[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightingShader.SetMat4("model", model);

			view = glm::lookAt(app.GetCamPos(), app.GetCamPos() + app.GetCamFront(), app.GetCamUp());
			lightingShader.SetMat4("view", view);

			projection = glm::perspective(glm::radians(app.GetFOV()), float(windowWidth) / windowHeight, 0.1f, 100.0f);
			lightingShader.SetMat4("projection", projection);

			c.Draw(1);
		}

		app.BufferSwapAndPoll();
	}

	return 0;
}
