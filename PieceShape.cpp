#include "PieceShape.h"
#include<fstream>
#include<iostream>

std::array<std::array< uint16_t, 4>, 4> PieceShape::PopulateShapeArray(uint16_t randomShape)
{
	return m_shape[randomShape];
}

	

void PieceShape::ReadShape()
{
	std::array<std::array<uint16_t, 4>, 4> piece;
	uint16_t type;
	int condition = 0;
	std::ifstream read("PiecesFile.txt");
	if (read.is_open())
	{
		while (condition!=8)
		{
			read >> type;
			for (uint16_t line = 0; line < 4; line++)
			{
				for (uint16_t column = 0; column < 4; column++)
				{
					read >> piece[line][column];
				}
			}
			m_shape[type] = piece;
			condition++;
		}
		read.close();
	}
	else std::cout << "Error!";
}

void PieceShape::ReadBigShape()
{
	std::array<std::array<uint16_t, 4>, 4> piece;
	uint16_t type;
	int condition = 0;
	std::ifstream read("BigPiecesFile.txt");
	if (read.is_open())
	{
		while (condition != 7)
		{
			read >> type;
			for (uint16_t line = 0; line < 4; line++)
			{
				for (uint16_t column = 0; column < 4; column++)
				{
					read >> piece[line][column];
				}
			}
			m_bigShape[type] = piece;
			condition++;
		}
		read.close();
	}
	else std::cout << "Error!";
}

std::array<std::array<uint16_t, 4>, 4> PieceShape::GetBigShape(uint16_t shapeAssigned)
{
	return m_bigShape[shapeAssigned];
}

