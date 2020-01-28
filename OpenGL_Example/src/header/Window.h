#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window();
	Window(int windowWidth_, int windowHeight_, std::string windowTitle);
	~Window();

	GLFWwindow* GetWindow();

private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
};

#endif	// WINDOW_H