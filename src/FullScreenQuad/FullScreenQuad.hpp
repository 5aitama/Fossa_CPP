#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../Components/Float2.hpp"

struct FullScreenQuad
{
public:
	FullScreenQuad();
	~FullScreenQuad();

	void const Draw();
private:
	/// <summary>
	/// Vertex arrays.
	/// </summary>
	GLuint vao;

	/// <summary>
	/// Vertex buffers.
	/// </summary>
	GLuint vbo[2];

	/// <summary>
	/// Vertex array.
	/// </summary>
	const Float2 vertices[4] = 
	{
		{ -1.0f, -1.0f },	// Bottom left
		{ -1.0f,  1.0f },	// Top left
		{  1.0f,  1.0f },	// Top right
		{  1.0f, -1.0f },	// Bottom right
	};

	/// <summary>
	/// Index array.
	/// </summary>
	const unsigned short indices[6] = 
	{
		0, 1, 2,	// First triangle
		0, 2, 3,	// Second triangle
	};
};

FullScreenQuad::FullScreenQuad()
{
	// Generate vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate vertex buffers
	glGenBuffers(2, vbo);

	// Push our vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Float2) * 4, vertices, GL_STATIC_DRAW);

	// Push our index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 6, indices, GL_STATIC_DRAW);

	// Attribute vertices to vertex
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, Float2::STRIDE, nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

FullScreenQuad::~FullScreenQuad()
{
	glDeleteBuffers(2, vbo);
	glDeleteBuffers(1, &vao);
}

void const FullScreenQuad::Draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}