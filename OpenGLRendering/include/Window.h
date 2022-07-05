#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string_view>

class Window 
{
private:
	GLFWwindow* window;

public:
	Window(int width, int height, std::string_view title);
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	~Window();

	void RunLoop();

protected:
	virtual void Setup() {}
	virtual void Update() {}
	virtual void Draw() {}
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
