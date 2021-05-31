#pragma once
#include<array>
#include<vector>
#include<random>
#include <ctime>
#include<string>

class Shape
{
public:
	enum class ShapeName
	{
		Square,
		I,
		L,
		LMirrored,
		Z,
		ZMirrored,
		T
	};

public:
	std::array<std::array< uint16_t, 4>, 4> GetArrayShape();
	Shape::ShapeName GetShape();
	std::array<std::array< uint16_t, 4>, 4> PopulateShapeArray(int randomShape);
	static std::string RandomStr(static std::string );
	uint16_t minX() const;
	uint16_t maxX() const;
	uint16_t minY() const;
	uint16_t maxY() const;

private:
	std::array<std::array< uint16_t, 4>, 4> m_shape;
	Shape::ShapeName m_shapeType;

private:
	Shape::ShapeName GetRandomShape();
};

