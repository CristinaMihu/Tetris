#pragma once
#include<array>
#include<vector>
#include<map>
#include<random>
#include <ctime>
#include<string>

class PieceShape
{

public:
	void ReadShape();
	void ReadBigShape();
	std::array<std::array< uint16_t, 4>, 4> GetBigShape(uint16_t shapeAssigned);
	std::array<std::array< uint16_t, 4>, 4> PopulateShapeArray(uint16_t randomShape);
	


private:
	std::map<uint16_t, std::array<std::array< uint16_t, 4>, 4>> m_shape;
	std::map<uint16_t, std::array<std::array< uint16_t, 4>, 4>> m_bigShape;
	
};

