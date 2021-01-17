#pragma once

#include <iostream>

struct Float2
{
public:
	static const size_t STRIDE = 2 * sizeof(float);
	float x;
	float y;
};