#pragma once
#include<array>
#include"PieceShape.h"
#include"Piece.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Block
{
public:
	void SetWidth(uint16_t width);
	void SetCellSize();
	std::array<std::array<uint16_t, 4>, 4> NewBlock(Piece& block, std::array<std::array<uint16_t, 4>, 4>& piece);
	std::array<std::array<uint16_t, 4>, 4> NewBlockPlayer1(Piece& block, std::array<std::array<uint16_t, 4>, 4>& player1);
	std::array<std::array<uint16_t, 4>, 4> NewBlockPlayer2(Piece& block, std::array<std::array<uint16_t, 4>, 4>& player2);
	void DrawBlock(int cx, int cy, sf::RenderWindow& window, sf::RectangleShape& cell, std::array<std::array<uint16_t, 4>, 4> piece, 
		std::array<std::array<uint16_t, 4>, 4> nextPiece, uint16_t colorAssigned, uint16_t nextColorAssigned);
	void DrawBlockPlayer1(int cx1, int cy1, sf::RenderWindow& window, sf::RectangleShape& cell, std::array<std::array<uint16_t, 4>, 4> player1,
		std::array<std::array<uint16_t, 4>, 4> nextPiecePlayer1, uint16_t colorAssigned, uint16_t nextColorAssigned);
	void DrawBlockPlayer2(int cx2, int cy2, sf::RenderWindow& window, sf::RectangleShape& cell, std::array<std::array<uint16_t, 4>, 4> player2,
		std::array<std::array<uint16_t, 4>, 4> nextPiecePlayer2, uint16_t colorAssigned, uint16_t nextColorAssigned);
private:
	uint16_t m_width;
	uint16_t cell_size;
};

