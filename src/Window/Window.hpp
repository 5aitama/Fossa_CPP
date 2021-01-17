#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

class Window
{
public:
	Window(const int& width, const int& height, const string& title);
	~Window();
	GLFWwindow* GetWindowPtr();

private:
	GLFWwindow* window_ptr = nullptr;
	string title = "no title";
	int width	= 800;
	int height	= 600;
};

Window::Window(const int& width, const int& height, const string& title)
{
	this->width		= width;
	this->height	= height;
	this->title		= title;

	window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!window_ptr)
		throw runtime_error("failed to create window");

	glfwMakeContextCurrent(window_ptr);
}

Window::~Window()
{
	if (window_ptr != nullptr)
		glfwDestroyWindow(window_ptr);
	
	glfwTerminate();
}

GLFWwindow* Window::GetWindowPtr()
{
	return window_ptr;
}