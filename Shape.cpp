#include "Shape.h"

std::array<std::array< uint16_t, 4>, 4> Shape::PopulateShapeArray(int randomShape)
{
	switch (randomShape)
	{
	case 0:
	{std::array<std::array< uint16_t, 4>, 4> m_Square
	{
		{{0, 0, 0, 0},
		{0, 1, 1,0 },
		{0, 1, 1, 0},
		{0, 0, 0, 0}}
	};
	return m_Square;
	m_shapeType = ShapeName::Square;
	break;
	}
	case 1:
	{std::array<std::array< uint16_t, 4>, 4> m_I
	{
		{{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0}}
	};
	return m_I;
	m_shapeType = ShapeName::I;
	break;
	}
	case 2: {
		std::array<std::array< uint16_t, 4>, 4> m_L
		{
			{{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}}
		};
		return m_L;
		m_shapeType = ShapeName::L;
		break;
	}
	case 3:
	{std::array<std::array< uint16_t, 4>, 4> m_LMirrored
	{
		{{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}}
	};
	return m_LMirrored;
	m_shapeType = ShapeName::LMirrored;
	break;
	}
	case 4:
	{std::array<std::array< uint16_t, 4>, 4> m_Z
	{
		{{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0}}
	};
	return m_Z;
	m_shapeType = ShapeName::Z;
	break; }
	case 5:
	{	std::array<std::array< uint16_t, 4>, 4> m_ZMirrored
	{
		{{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}}
	};
	return m_ZMirrored;
	m_shapeType = ShapeName::ZMirrored;
	break; }
	case 6:
	{std::array<std::array< uint16_t, 4>, 4> m_T
	{
		{{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}}
	};
	return m_T;
	m_shapeType = ShapeName::T;
	break; }

	}

}

std::string Shape::RandomStr(const std::string a)
{
	static std::mt19937 rng(std::time(0));
	static std::uniform_int_distribution<std::size_t> distr(0, a.size() - 1);

	std::string r;
	r = a[distr(rng)];
	return r;
}

Shape::ShapeName Shape::GetRandomShape()
{
	std::string rand = RandomStr("0123456");
	switch (stoi(rand))
	{
	case 0:
		return ShapeName::Square;
	case 1:
		return ShapeName::I;
	case 2:
		return ShapeName::L;
	case 3:
		return ShapeName::LMirrored;
	case 4:
		return ShapeName::Z;
	case 5:
		return ShapeName::ZMirrored;
	case 6:
		return ShapeName::T;
	}
}

std::array<std::array<uint16_t, 4>, 4> Shape::GetArrayShape()
{
	return m_shape;
}

Shape::ShapeName Shape::GetShape()
{
	return m_shapeType;
}

uint16_t Shape::minX() const
{
	uint16_t min = m_shape[0][0];
	for (uint16_t i = 1; i < 4; ++i)
		min = std::min(min, m_shape[i][0]);
	return min;
}

uint16_t Shape::maxX() const
{
	uint16_t max = m_shape[0][0];
	for (uint16_t i = 1; i < 4; ++i)
		max = std::max(max, m_shape[i][0]);
	return max;
}

uint16_t Shape::minY() const
{
	uint16_t min = m_shape[0][0];
	for (uint16_t i = 1; i < 4; ++i)
		min = std::min(min, m_shape[i][1]);
	return min;
}

uint16_t Shape::maxY() const
{
	uint16_t max = m_shape[0][0];
	for (uint16_t i = 1; i < 4; ++i)
		max = std::max(max, m_shape[i][1]);
	return max;
}