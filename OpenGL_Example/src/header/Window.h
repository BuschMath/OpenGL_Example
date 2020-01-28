#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

enum class InputModeType
{
	CURSOR, STICKY_KEYS, STICKY_MOUSE, LOCK_KEY_MODS, RAW_MOUSE_MOTION
};

enum class InputValueType
{
	NORMAL, HIDDEN, DISABLED, TRUE, FALSE
};

class Window
{
public:
	Window();
	Window(int windowWidth_, int windowHeight_, std::string windowTitle);
	~Window();
	
	GLFWwindow* GetWindow();
	void SetInputMode(InputModeType mode, InputValueType value);

private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
};

#endif	// WINDOW_H