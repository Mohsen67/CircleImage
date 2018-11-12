#pragma once
#include <vector>

class Circle
{
public:
	Circle(int radius, int centerX, int centerY, int width, int height);
	std::vector<std::vector<unsigned char>> Data{};
	~Circle();
};

