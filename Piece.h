#pragma once
#include<array>
#include"PieceShape.h"
#include<iostream>
class Piece
{
public:
	enum class Colors
	{
		green,
		blue,
		magenta,
		yellow,
		white,
		cyan
	};

public:

	std::array<std::array< uint16_t, 4>, 4> GetMemberPiece();
	uint16_t GetMemberColor();
	void AssignShape(Piece::Colors color, uint16_t randomShape);
	Colors GetRandomColor(int randomColor);
	void GetRandomRotation(int randomRotation, int randomColor, uint16_t randomShape, int conditon);
	void MatrixDisplay(std::array<std::array< uint16_t, 4>, 4>);
	static std::array<std::array<uint16_t, 4>, 4> RotateBlockAtCommand(std::array<std::array< uint16_t, 4>, 4> piece);
	std::array<std::array<uint16_t, 4>, 4> IncrasePiece(int colorAssigned, int rotationAssigned, uint16_t shapeAssigned);

private:
	PieceShape m_shape;
	Colors m_color;
	std::array<std::array<uint16_t, 4>, 4> m_piece;
};