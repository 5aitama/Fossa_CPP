#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <filesystem>
#include <GLFW/glfw3.h>

#include "Window/Window.hpp"
#include "Shader/Shader.hpp"
#include "Components/Float2.hpp"
#include "FullScreenQuad/FullScreenQuad.hpp"

namespace fs = std::filesystem;

void main(int argc, char** argv)
{
	// Initialize GLFW...
	if (!glfwInit())
		throw runtime_error("Failed to initialize glfw !");

	// Create our game window
	Window window(800, 600, "My window");

	// Init GLEW
	const GLenum err = glewInit();

	// Check the initialization of glew...
	if (err != GLEW_OK)
		throw glewGetErrorString(err);

	// Get the window ptr
	const auto windowPtr = window.GetWindowPtr();

	// Check the folder path.that contains shaders..
	const auto shader_path = fs::path(fs::current_path().string() + "/shaders");

	// Throw beautiful exception..
	if (!fs::exists(shader_path))
		throw exception("Shaders folder not found!");

	// Our vertex shader path...
	const string v_shader_path = shader_path.string() + "/basic/basic.vert";
	// Our fragment shader path...
	const string f_shader_path = shader_path.string() + "/basic/basic.frag";

	// Create new shader and compile it...
	auto simpleShader = Shader(v_shader_path, f_shader_path);
	simpleShader.Compile();

	// Our shader program...
	const auto program = simpleShader.GetProgram();

	// Use our compiled shader...
	glUseProgram(simpleShader.GetProgram());

	// Create a full screen quad to apply the shader on it....
	auto fullScreenQuad = FullScreenQuad();
	
	// Get the uniform properties location from the shader
	const auto iResolution	= glGetUniformLocation(program, "iResolution");
	const auto iTime		= glGetUniformLocation(program, "iTime");

	// Our game loop...
	while (!glfwWindowShouldClose(windowPtr))
	{
		// Retreive the current window size...
		int width, height;
		glfwGetWindowSize(windowPtr, &width, &height);

		// Set the viewport according to the window size...
		glViewport(0, 0, width, height);

		// Clear buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Set a background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// Set uniform properties on the shader...
		glUniform2f(iResolution, static_cast<GLfloat>(width), static_cast<GLfloat>(height));
		glUniform1f(iTime, static_cast<GLfloat>(glfwGetTime()));

		// Draw our fullscreen quad...
		fullScreenQuad.Draw();

		// Swap buffers and pool events...
		glfwSwapBuffers(windowPtr);
		glfwPollEvents();
	}

}