#ifndef APP_H
#define APP_H

#include "Camera.h"
#include "Window.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class App
{
public:
	App();
	App(int windowWidth_, int windowHeight_, std::string windowTitle, glm::vec3 iniCamPos, glm::vec3 iniCamFront, 
		glm::vec3 iniCamUp, float iniFOV);
	~App();

	GLFWwindow* GetWindow() {return window->GetWindow(); };
	void SetInputMode(InputModeType mode, InputValueType value) { window->SetInputMode(mode, value); };

	void SetCamPos(glm::vec3 newCamPos) { camera->SetCamPos(newCamPos); };
	glm::vec3 GetCamPos() { return camera->GetCamPos(); };

	void SetCamFront(glm::vec3 newCamFront) { camera->SetCamPos(newCamFront); };
	glm::vec3 GetCamFront() { return camera->GetCamFront(); };

	void SetCamUp(glm::vec3 newCamUp) { camera->SetCamUp(newCamUp); };
	glm::vec3 GetCamUp() { return camera->GetCamUp(); };

	void SetFOV(float newFOV) { camera->SetFOV(newFOV); };
	float GetFOV() { return camera->GetFOV(); };

	void HandleMouse();
	void HandleScroll(GLFWwindow* window, double xoffset, double yoffset);
private:
	Window* window;
	Camera* camera;

};

#endif // !APP_H
