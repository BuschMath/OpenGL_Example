#include "Camera.h"

Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;
}

Camera::Camera(glm::vec3 iniCamPos, glm::vec3 iniCamFront, glm::vec3 iniCamUp, float iniFOV)
{
	cameraPos = iniCamPos;
	cameraFront = iniCamFront;
	cameraUp = iniCamUp;
	fov = iniFOV;
}

Camera::~Camera()
{
}
