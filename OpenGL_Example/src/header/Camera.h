#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 iniCamPos, glm::vec3 iniCamFront, glm::vec3 iniCamUp, float iniFOV);

	~Camera();

	void SetCamPos(glm::vec3 newCamPos) { cameraPos = newCamPos; };
	glm::vec3 GetCamPos() { return cameraPos; };

	void SetCamFront(glm::vec3 newCamFront) { cameraFront = newCamFront; };
	glm::vec3 GetCamFront() { return cameraFront; };

	void SetCamUp(glm::vec3 newCamUp) { cameraUp = newCamUp; };
	glm::vec3 GetCamUp() { return cameraUp; };

	void SetFOV(float newFOV) { fov = newFOV; };
	float GetFOV() { return fov; };

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float fov;
};

#endif // !CAMERA_H

