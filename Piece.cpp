#include "Piece.h"
#include<iostream>
#include<random>



std::array<std::array< uint16_t, 4>, 4> Piece::GetMemberPiece()
{
	return m_piece;
}

uint16_t Piece::GetMemberColor()
{
	return static_cast<uint16_t>(m_color);
}

void Piece::AssignShape(Piece::Colors color, uint16_t randomShape)
{
	m_shape.ReadShape();
	m_piece = m_shape.PopulateShapeArray(randomShape);
	m_color = color;
}

Piece::Colors Piece::GetRandomColor(int randomColor)
{
	switch (randomColor)
	{
	case 0:
		return Colors::green;
	case 1:
		return Colors::blue;
	case 2:
		return Colors::magenta;
	case 3:
		return Colors::cyan;
	case 4:
		return Colors::yellow;
	}
	return Colors::white;
}

void Piece::GetRandomRotation(int randomRotation, int randomColor, uint16_t randomShape, int condition)
{
	if(condition==0)
	AssignShape(GetRandomColor(randomColor), randomShape);

	switch (randomRotation)
	{
	case 0:
	{
		uint16_t aux;
		for (uint16_t line = 0; line < 2; line++)
		{

			for (uint16_t column = line; column < 3 - line; column++)
			{
				aux = m_piece[line][column];
				m_piece[line][column] = m_piece[3 - column][line];
				m_piece[3 - column][line] = m_piece[3 - line][3 - column];
				m_piece[3 - line][3 - column] = m_piece[column][3 - line];
				m_piece[column][3 - line] = aux;
			}

		}
		break;
	}
	case 1:
	{
		uint16_t line2 = 3;
		uint16_t column2;
		for (uint16_t line = 0; line < 4; line++)
		{
			column2 = 3;

			for (uint16_t column = 0; column < 2; column++)
			{
				std::swap(m_piece[line][column], m_piece[line2][column2]);
				column2--;
			}
			line2--;
		}
		break;
	}
	case 2:
	{
		for (int line = 0; line < 3; line++)
		{

			for (int column = 3; column > line; column--)
			{
				std::swap(m_piece[line][column], m_piece[column][line]);

			}

		}
		break;

	}
	case 3:
	{
		break;

	}

	}

}




void Piece::MatrixDisplay(std::array<std::array< uint16_t, 4>, 4> array)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << array[i][j] << " ";
		std::cout << std::endl;
	}
}
std::array<std::array<uint16_t, 4>, 4> Piece::RotateBlockAtCommand(std::array<std::array< uint16_t, 4>, 4> piece)
{
	uint16_t aux;
	uint16_t variable = 3;
	for (int line = 0; line < 2; line++)
	{
		for (int column = line; column < variable - line; column++)
		{
			aux = piece[line][column];
			piece[line][column] = piece[variable - column][line];
			piece[variable - column][line] = piece[variable - line][variable - column];
			piece[variable - line][variable - column] = piece[column][variable - line];
			piece[column][variable - line] = aux;
		}

	}
	return piece;
}

std::array<std::array<uint16_t, 4>, 4> Piece::IncrasePiece(int colorAssigned, int rotationAssigned, uint16_t shapeAssigned)
{
	m_shape.ReadBigShape();
	m_piece = m_shape.GetBigShape(shapeAssigned);
	GetRandomRotation(rotationAssigned, colorAssigned, shapeAssigned, 1);
	return m_piece;
}





