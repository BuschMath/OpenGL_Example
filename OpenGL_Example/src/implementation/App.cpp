#include "App.h"

#include <glfw/glfw3.h>
#include <iostream>

// Global variables
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch;
bool firstMouse = true;

App::App()
{
	window = nullptr;
	camera = nullptr;
}

App::App(int windowWidth_, int windowHeight_, std::string windowTitle, glm::vec3 iniCamPos, 
	glm::vec3 iniCamFront, glm::vec3 iniCamUp, float iniFOV)
{
	window = new Window(windowWidth_, windowHeight_, windowTitle);

	glfwSetWindowUserPointer(window->GetWindow(), this);

	glfwSetScrollCallback(window->GetWindow(), [](GLFWwindow* window, double x, double y)
		{
			if (App* app = static_cast<App*>(glfwGetWindowUserPointer(window)))
				app->HandleScroll(window, x, y);
		});

	camera = new Camera(iniCamPos, iniCamFront, iniCamUp, iniFOV);
}

App::~App()
{
}

void App::HandleMouse()
{
	GLdouble xpos, ypos;
	glfwGetCursorPos(window->GetWindow(), &xpos, &ypos);

	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;	// Reveresed on purpose
	lastX = (float)xpos;
	lastY = (float)ypos;

	const float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = 89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera->SetCamFront(glm::normalize(direction));
}

void App::HandleScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (camera->GetFOV() >= 1.0f && camera->GetFOV() <= 45.0f)
		camera->SetFOV(camera->GetFOV() - (float)yoffset);
	if (camera->GetFOV()<= 1.0f)
		camera->SetFOV(1.0f);
	if (camera->GetFOV()>= 45.0f)
		camera->SetFOV(45.0f);
}
