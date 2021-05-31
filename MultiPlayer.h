#pragma once
#include"Piece.h"
#include"PieceShape.h"
#include"Score.h"
#include"Block.h"
#include"BoardSFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
class MultiPlayer
{
public:
	MultiPlayer();
	~MultiPlayer();
	void SetBoard(std::array<std::array<uint16_t, 10>, 30> board);
	MultiPlayer(std::array<std::array<uint16_t, 4>, 4 >player1, std::array<std::array<uint16_t, 4>, 4 >player2);
	void SetParametersForPlayAgain();
	void ReadImageAndFontPath();
	void RandomgenerateValues(uint16_t& colorAssigned, uint16_t& shapeAssigned, uint16_t& rotationAssigned);
	void FallPiece(std::array<std::array<uint16_t, 4>, 4> &piece, std::array<std::array<uint16_t, 4>, 4>& nextPiece, uint16_t& colorAssigned,
		uint16_t& shapeAssigned, uint16_t& rotationAssigned, uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, uint16_t& nextRotationAssigned, int& cx, int& cy);
	void DeleteBlackHole(bool& existBlackHole, bool& pieceTouchesBlackHole, uint16_t coordY, uint16_t coordX);
	void GenerateRandomBlackHole(bool& existBlackHole, uint16_t& coordX, uint16_t& coordY, sf::RectangleShape cell, sf::RenderWindow& window);
	void DrawWindow(uint16_t score, uint16_t level,sf::Sprite background, sf::RectangleShape cell, sf::RenderWindow& window);
	void StartMultiPlayerGame();
	bool Fall(std::array<std::array<uint16_t, 4>, 4 > piece, std::array<std::array<uint16_t, 4>, 4 > nextPiece, uint16_t coordX,
		uint16_t coordY, int cx, int cy, bool existBlackHole,
		bool pieceTouchesBlackHole, uint16_t shapeAssigned, uint16_t colorAssigned,
		uint16_t nextColorAssigned, uint16_t nextRotationAssigned, uint16_t nextShapeAssigned, uint16_t rotationAssigned);
	void SetCurrentPiece(std::array<std::array<uint16_t, 4>, 4 >& piece, uint16_t& colorAssigned, uint16_t& shapeAssigned, uint16_t& rotationAssigned, int& cx, int& cy);
	void SetNextPiece(std::array<std::array<uint16_t, 4>, 4 >&  nextPiece,uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, 
		uint16_t& nextRotationAssigned, int& cx, int& cy);
	void SetCoordinates(int& cx1, int& cy1, int& cx2, int& cy2);
	


private:
	BoardSFML<10, 30> gameBoard;
	SFMLItems graphics;
	Piece block;
	Block blockObject;
	Score object;

private:
	int cx1, cx2;
	int cy1, cy2;
	uint16_t colorAssignedPlayer1, colorAssignedPlayer2;
	uint16_t rotationAssignedPlayer1, rotationAssignedPlayer2;
	uint16_t shapeAssignedPlayer1, shapeAssignedPlayer2;
	uint16_t nextColorAssignedPlayer1, nextColorAssignedPlayer2;
	uint16_t nextRotationAssignedPlayer1, nextRotationAssignedPlayer2;
	uint16_t nextShapeAssignedPlayer1, nextShapeAssignedPlayer2;
	uint16_t score;
	uint16_t verify;
	uint16_t level;
	uint16_t increaseLevelUp;


private:
	sf::Text scoreText;
	sf::Text highScoreText;
	sf::Text levelText;
	sf::Font font;

private:
	std::array<std::array<uint16_t, 4>, 4 > piecePlayer1;
	std::array<std::array<uint16_t, 4>, 4 > piecePlayer2;
	std::array<std::array<uint16_t, 4>, 4 > nextPiecePlayer1;
	std::array<std::array<uint16_t, 4>, 4 > nextPiecePlayer2;
	std::array<std::array<uint16_t, 4>, 4 > auxiliarPiecePlayer1;
	std::array<std::array<uint16_t, 4>, 4 > auxiliarPiecePlayer2;
	std::array<std::array<uint16_t, 10>, 30> board;

private:
	bool m_playAgain;
	bool m_gameover;

private:
	std::string imagePlayAgainPath, imageTetrisPath, imageGameOverPath, fontPath;
};

