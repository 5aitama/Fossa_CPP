#pragma once

#include <iostream>

struct Float3
{
public:
	static const size_t STRIDE = 3 * sizeof(float);
	float x;
	float y;
	float z;
};