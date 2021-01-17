#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

struct Shader
{
private:
	/// <summary>
	/// The shader program id.
	/// </summary>
	GLuint program;

	/// <summary>
	/// The vertex shader file path.
	/// </summary> 
	const string& vertex_shader_path;

	/// <summary>
	/// The fragment shader file path.
	/// </summary>
	const string& fragment_shader_path;

public:
	/// <summary>
	/// Create new shader.
	/// </summary>
	/// <param name="vertex_shader_path">Vertex shader file path</param>
	/// <param name="fragment_shader_path">Fragment shader file path</param>
	Shader(const string& vertex_shader_path, const string& fragment_shader_path);
	~Shader();

	/// <summary>
	/// Compile vertex and fragment shader code.
	/// </summary>
	void Compile();

	/// <summary>
	/// Return the shader program id.
	/// </summary>
	GLuint GetProgram();

	/// <summary>
	/// Read all file content.
	/// </summary>
	/// <param name="file_path">Path of the file to read</param>
	const string ReadFile(const string& file_path);
};

Shader::Shader(const string& vertex_shader_path, const string& fragment_shader_path) : 
	vertex_shader_path(vertex_shader_path), 
	fragment_shader_path(fragment_shader_path),
	program(NULL)
{

}

Shader::~Shader()
{
	// Delete the program if it was created...
	if (glIsProgram(program) == GL_TRUE)
		glDeleteProgram(program);
}

const string Shader::ReadFile(const string& file_path)
{
	auto stream = ifstream(file_path);
	auto content = string((istreambuf_iterator<char>(stream)), (istreambuf_iterator<char>()));

	return content;
}

GLuint Shader::GetProgram()
{
	return program;
}

void Shader::Compile()
{
	// Read our shaders into the appropriate buffers
	const string vertexSource = ReadFile(vertex_shader_path); // Get source code for vertex shader.
	const string fragmentSource = ReadFile(fragment_shader_path); // Get source code for fragment shader.

	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		throw runtime_error((const char*)infoLog.data());
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		cout << infoLog.data() << endl;
		throw runtime_error((const char*)infoLog.data());
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	program = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.
		cout << (const char*)infoLog.data() << endl;
		throw runtime_error((const char*)infoLog.data());
	}

	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
}