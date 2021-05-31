#include "Block.h"

const sf::Color color_map[] =
{
	sf::Color::Green,sf::Color::Blue,sf::Color::Magenta,sf::Color::Yellow,sf::Color::White,sf::Color::Cyan
};
void Block::SetWidth(uint16_t width)
{
	m_width = width;
}
void Block::SetCellSize()
{
	cell_size = 30;
}
std::array<std::array<uint16_t, 4>, 4> Block::NewBlock(Piece& block, std::array<std::array<uint16_t, 4>, 4>& piece)
{
	piece = block.GetMemberPiece();
	return piece;
}
std::array<std::array<uint16_t, 4>, 4> Block::NewBlockPlayer1(Piece& block, std::array<std::array<uint16_t, 4>, 4>& player1)
{
	player1= block.GetMemberPiece();
	return player1;
}
std::array<std::array<uint16_t, 4>, 4> Block::NewBlockPlayer2(Piece& block, std::array<std::array<uint16_t, 4>, 4>& player2)
{
	player2 = block.GetMemberPiece();
	return player2;
}
void Block::DrawBlock(int cx, int cy, sf::RenderWindow& window, sf::RectangleShape& cell, std::array<std::array<uint16_t, 4>, 4> piece, std::array<std::array<uint16_t, 4>, 4> nextPiece, uint16_t colorAssigned, uint16_t nextColorAssigned)
{
	cell.setFillColor(color_map[colorAssigned]);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (piece[i][j])
			{
				cell.setOutlineColor(sf::Color::Black);
				cell.setOutlineThickness(1.f);
				cell.setPosition(sf::Vector2f((cx + j) * cell_size, (cy + i) * cell_size));
				window.draw(cell);
			}

	cell.setFillColor(color_map[nextColorAssigned]);
	for (int i = 0; i < 120; i += 30)
		for (int j = 0; j < 120; j += 30)
			if (nextPiece[i / 30][j / 30] == 1) {
				cell.setPosition(i + 355, j + 235);
				window.draw(cell);
			}
}
void Block::DrawBlockPlayer1(int cx1, int cy1, sf::RenderWindow& window, sf::RectangleShape& cell, std::array<std::array<uint16_t, 4>, 4> player1, 
	std::array<std::array<uint16_t, 4>, 4> nextPiecePlayer1, uint16_t colorAssigned, uint16_t nextColorAssigned)
{
	cell.setFillColor(color_map[colorAssigned]);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (player1[i][j])
			{
				cell.setOutlineColor(sf::Color::Black);
				cell.setOutlineThickness(1.f);
				cell.setPosition(sf::Vector2f((cx1 + j) * cell_size, (cy1 + i) * cell_size));
				window.draw(cell);
			}

	cell.setFillColor(color_map[nextColorAssigned]);
	for (int i = 0; i < 120; i += 30)
		for (int j = 0; j < 120; j += 30)
			if (nextPiecePlayer1[i / 30][j / 30] == 1) {
				cell.setPosition(i + 313, j + 743);
				window.draw(cell);
			}
}

void Block::DrawBlockPlayer2(int cx2, int cy2, sf::RenderWindow& window, sf::RectangleShape& cell, std::array<std::array<uint16_t, 4>, 4> player2,
	std::array<std::array<uint16_t, 4>, 4> nextPiecePlayer2, uint16_t colorAssigned, uint16_t nextColorAssigned)
{

	cell.setFillColor(color_map[colorAssigned]);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (player2[i][j])
			{
				cell.setOutlineColor(sf::Color::Black);
				cell.setOutlineThickness(1.f);
				cell.setPosition(sf::Vector2f((cx2 + j) * cell_size, (cy2 + i) * cell_size));
				window.draw(cell);
			}

	cell.setFillColor(color_map[nextColorAssigned]);
	for (int i = 0; i < 120; i += 30)
		for (int j = 0; j < 120; j += 30)
			if (nextPiecePlayer2[i / 30][j / 30] == 1) {
				cell.setPosition(i + 313, j + 885);
				window.draw(cell);
			}

}
