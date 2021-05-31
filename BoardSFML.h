#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Piece.h"
#include"PieceShape.h"
#include"SFMLItems.h"
#include<array>
#include <algorithm>

const sf::Color color_map[] =
{
	sf::Color::Green,sf::Color::Blue,sf::Color::Magenta,sf::Color::Yellow,sf::Color::White,sf::Color::Cyan
};
template<typename uint16_t size1, typename uint16_t size2>
class BoardSFML
{
public:

	void SetWidthAndHight(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	template<typename uint16_t size1, typename uint16_t size2>
	void SetBoard(std::array<std::array<uint16_t, size1>, size2> board)
	{
		m_board = board;
	}
	template<typename uint16_t size1, typename uint16_t size2>
	std::array<std::array<uint16_t, size1>, size2> GetBoard()
	{
		return m_board;
	}

	template<typename uint16_t size1, typename uint16_t size2>
	bool CheckBlock(std::array<std::array<uint16_t, 4>, 4>& piece, int& coordinateX, int& coordinateY, bool& pieceTouchesBlackHole)
	{
		{
			for (int line = 0; line < 4; line++)
				for (int column = 0; column < 4; column++)
				{
					if (piece[line][column] == 0)
						continue;
					if (column + coordinateX < 0 || column + coordinateX >= width || line + coordinateY >= height)
						return false;

					if (m_board[coordinateY + line][coordinateX + column] != 0 && m_board[coordinateY + line][coordinateX + column] != 10)
						return false;
					if (m_board[coordinateY + line][coordinateX + column] == 10)
					{
						graphics.ReadMusicPath();
						graphics.PlayMusicVanish();
						piece[line][column] = 0;
						pieceTouchesBlackHole = true;
						m_board[coordinateY + line][coordinateX + column] = 0;


					}
				}
			return true;
		}
	}
	
	void DrawBoard(bool& gameover, sf::RectangleShape& cell, sf::RenderWindow& window)
	{
		
		std::vector<int> firstLine;
		for (int i = 0; i < width ; i++)
		{
			firstLine.push_back(m_board[2][i]);
		}
		
		if(std::any_of(firstLine.begin(), firstLine.end(), [firstLine](int i) {  return (firstLine[i]!=0 && firstLine[i]!=10); })) 
		{
			gameover = true;
			graphics.ReadMusicPath();
			graphics.PlayMusicGameOver();
		}
		firstLine.clear();
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (m_board[y][x] != 0 && m_board[y][x] != 10 && m_board[y][x] != 11)
				{

					cell.setFillColor(color_map[m_board[y][x] - 1]);
					cell.setOutlineColor(sf::Color::Black);
					cell.setOutlineThickness(1.f);
					cell.setPosition(sf::Vector2f(x * cell_size, y * cell_size));
					window.draw(cell);
				}
				if (m_board[y][x] == 10)
				{
					cell.setFillColor(sf::Color::Red);
					cell.setOutlineColor(sf::Color::Black);
					cell.setOutlineThickness(1.f);
					cell.setPosition(sf::Vector2f(x * cell_size, y * cell_size));
					window.draw(cell);
				}

			}
		}
	}
	void ClearLine(uint16_t& score, uint16_t& verify, uint16_t& level, uint16_t& incraseLevelUp, uint16_t& coordY)
	{
		int line = height - 1;
		for (int i = height - 1; i >= 0; i--)
		{
			int count = 0;
			for (int j = 0; j < width; j++)
				if (m_board[i][j] != 0 && m_board[i][j] != 10)
					count++;

			if (count < width)
			{
				for (int j = 0; j < width; j++)
					m_board[line][j] = m_board[i][j];

				line--;


			}
			else
			{
				coordY++;
				graphics.PlayMusicDeleteLine();
				score += 10;
				verify++;

				if (verify == incraseLevelUp) {
					level += 1;
					verify = 0;
					incraseLevelUp += 2;
				}
			}

		}
	}


	void LastEmptyPosition(int column)
	{
		for (int line = height - 1; line >= 0; line--)
			if (m_board[line][column] == 0)
			{
				m_board[line + 1][column] = 11;
				break;
			}
	}
	bool CheckBlockForCell(std::array<std::array<uint16_t, 4>, 4>& piece, int& coordinateX, int& coordinateY, bool& pieceTouchesBlackHole)
	{
		for (int line = 0; line < 4; line++)
			for (int column = 0; column < 4; column++)
			{
				if (piece[line][column] == 0)
					continue;
				if (column + coordinateX < 0 || column + coordinateX >= width || line + coordinateY >= height)
					return false;
				LastEmptyPosition(coordinateX + column);
				if (m_board[coordinateY + line][coordinateX + column] == 11)
					return false;
				if (m_board[coordinateY + line][coordinateX + column] == 10)
				{
					graphics.PlayMusicVanish();
					piece[line][column] = 0;
					m_board[coordinateY + line][coordinateX + column] = 0;

				}

			}
		return true;
	}

private:
	int width;
	int height;
	float cell_size = 30;

private:
	std::array<std::array<uint16_t, size1>, size2> m_board = { 0 };

private:
	SFMLItems graphics;

};

