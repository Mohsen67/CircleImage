#include "pch.h"
#include "Circle.h"
#include <vector>
#include <memory>

Circle::Circle(const int radius, const int centerX, const int centerY, const int width, const int height)
{
	Data.resize(width, std::vector<unsigned char>(height, 0));

	if (radius < 0 || centerX < 0 || centerY <0)
	return;

	auto startX = centerX - radius > 0 ? centerX - radius : 0;
	auto endX = centerX + radius < width ? centerX + radius : width;
	auto startY = centerY - radius > 0 ? centerY - radius : 0;
	auto endY = centerY + radius < height ? centerY + radius : height;

	for (auto i = startX; i < endX; i++)
	{
		for (auto j = startY; j < endY; j++)
		{
			auto distance = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));
			if (distance <= static_cast<double>(radius))
				Data[i][j] = UCHAR_MAX;
		}
	}
}

Circle::~Circle()
= default;
