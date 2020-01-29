#include "App.h"

App::App()
{
}

App::App(int windowWidth_, int windowHeight_, std::string windowTitle, glm::vec3 iniCamPos, glm::vec3 iniCamFront, glm::vec3 iniCamUp, float iniFOV)
{
	window = new Window(windowWidth_, windowHeight_, windowTitle);
}

App::~App()
{
}
