#pragma once
#include"Piece.h"
#include"PieceShape.h"
#include"Score.h"
#include"BoardSFML.h"
#include "Block.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Game
{
public:
	
	void SetBoard(std::array<std::array<uint16_t, 10>, 20> board);
	void SetCurrentPiece();
	void SetNextPiece(uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, uint16_t& nextRotationAssigned);
	void SetParametersForPlayAgain();
	void ReadImageAndFontPath();
	void RandomgenerateValues(uint16_t& colorAssigned, uint16_t& shapeAssigned, uint16_t& rotationAssigned);
	void FallPiece(uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, uint16_t& nextRotationAssigned);
	void DeleteBlackHole(bool& existBlackHole, bool& pieceTouchesBlackHole, uint16_t coordY, uint16_t coordX);
	void GenerateRandomBlackHole(bool& existBlackHole, uint16_t& coordX, uint16_t& coordY, sf::RectangleShape cell, sf::RenderWindow& window);
	void DrawWindow(uint16_t score, uint16_t level, uint16_t nextColorAssigned, sf::Sprite background, sf::RectangleShape cell, sf::RenderWindow& window);
	void StartGame();
	bool IsSpriteHover(sf::FloatRect sprite, sf::Vector2f mp);
	bool GetMemberGameOver();
	bool GetMemberPlayAgain();
	void SetCoordinates(int& cx, int& cy);

private:
	bool m_playAgain;
	bool m_gameover;

private:
	Piece block;
	BoardSFML<10,20> gameBoard;
	Score object;
	SFMLItems graphics;
	Block blockObject;

private:
	std::array<std::array<uint16_t, 4>, 4> piece;
	std::array<std::array<uint16_t, 4>, 4> piecePlayer2;
	std::array<std::array<uint16_t, 4>, 4> nextPiece;
	std::array<std::array<uint16_t, 4>, 4> aux;
	std::array<std::array<uint16_t, 4>, 4> auxiliarPiece;
	std::array<std::array<uint16_t, 10>, 20> board;

private:
	int cx;
	int cy;
	uint16_t colorAssigned;
	uint16_t rotationAssigned;
	uint16_t shapeAssigned;

private:
	sf::Text scoreText;
	sf::Text highScoreText;
	sf::Text levelText;

private:
	sf::Font font;

private:
	sf::Texture imageTexture, tGameOver;

private:
	std::string imagePlayAgainPath, imageTetrisPath, imageGameOverPath, fontPath;


	

};

