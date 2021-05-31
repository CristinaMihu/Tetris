#include "MultiPlayer.h"
#include"Game.h"
#include<fstream>
MultiPlayer::MultiPlayer()
{

}

MultiPlayer::~MultiPlayer()
{
}

void MultiPlayer::SetBoard(std::array<std::array<uint16_t, 10>, 30> board)
{
	this->board = board;
}

MultiPlayer::MultiPlayer(std::array<std::array<uint16_t, 4>, 4> player1, std::array<std::array<uint16_t, 4>, 4> player2)
{
	std::copy(std::begin(player1), std::end(player1), std::begin(piecePlayer1));
	std::copy(std::begin(player2), std::end(player2), std::begin(piecePlayer2));
}

void MultiPlayer::SetParametersForPlayAgain()
{
	this->m_gameover = false;
	this->board = { 0 };
	this->piecePlayer1 = { 0 };
	this->piecePlayer2 = { 0 };
	this->nextPiecePlayer1 = { 0 };
	this->nextPiecePlayer2 = { 0 };
	this->auxiliarPiecePlayer1 = { 0 };
	this->auxiliarPiecePlayer2 = { 0 };
	this->m_playAgain = true;
	gameBoard.SetBoard(board);

}
void MultiPlayer::ReadImageAndFontPath()
{
	std::ifstream readImage("ImageMultiPlayerPath.txt");

	while (!readImage.eof())
	{
		readImage >> imagePlayAgainPath;
		readImage >> imageTetrisPath;
		readImage >> imageGameOverPath;
		readImage >> fontPath;
	}
	readImage.close();
}
const float cell_size = 30;
const int width = 10;
const int height = 30;

void MultiPlayer::RandomgenerateValues(uint16_t& colorAssigned, uint16_t& shapeAssigned, uint16_t& rotationAssigned)
{
	colorAssigned = rand() % 6;
	shapeAssigned = rand() % 8;
	rotationAssigned = rand() % 4;
}

void MultiPlayer::FallPiece(std::array<std::array<uint16_t, 4>, 4> &piece, std::array<std::array<uint16_t, 4>, 4>& nextPiece, uint16_t& colorAssigned,
	uint16_t& shapeAssigned, uint16_t &rotationAssigned, uint16_t& nextColorAssigned, uint16_t &nextShapeAssigned, uint16_t& nextRotationAssigned, int& cx, int &cy)
{
	cy--;
	for (uint16_t line = 0; line < 4; line++)
		for (uint16_t column = 0; column < 4; column++)
			if (piece[line][column])
			{

				board[cy + line][cx + column] = colorAssigned + 1;
				gameBoard.SetBoard(board);

			}
	piece = std::move(nextPiece);
	colorAssigned = nextColorAssigned;
	shapeAssigned = nextShapeAssigned;
	rotationAssigned = nextRotationAssigned;

}

void MultiPlayer::DeleteBlackHole(bool& existBlackHole, bool& pieceTouchesBlackHole, uint16_t coordY, uint16_t coordX)
{
	board[coordY][coordX] = 0;
	gameBoard.SetBoard(board);
	existBlackHole = false;
	pieceTouchesBlackHole = false;
}

void MultiPlayer::GenerateRandomBlackHole(bool& existBlackHole, uint16_t& coordX, uint16_t& coordY, sf::RectangleShape cell, sf::RenderWindow& window)
{
	uint16_t	random = rand() % 10000;
	if (random == 7 && m_gameover == false && existBlackHole == false)
	{
		coordX = rand() % width;
		coordY = rand() % height;
		existBlackHole = true;
		if (coordY == 0) coordY += 3;
		if (board[coordY][coordX] != 0)
		{
			board[coordY][coordX] = 0;
			SetBoard(board);
			existBlackHole = false;
			graphics.PlayMusicVanish();
			cell.setFillColor(sf::Color::Red);
			cell.setOutlineColor(sf::Color::Black);
			cell.setOutlineThickness(1.f);
			cell.setPosition(sf::Vector2f(coordX * cell_size, coordY * cell_size));
			window.draw(cell);
		}
		else
		{

			board[coordY][coordX] = 10;
			graphics.PlayMusicBlackHole();

		}
	}
}

void MultiPlayer::DrawWindow(uint16_t score, uint16_t level, sf::Sprite background, sf::RectangleShape cell, sf::RenderWindow& window)
{
	object.SetScore(score);
	object.SetLevel(level);
	object.SetHighScore();
	object.checkHighScore(score);
	scoreText = object.MakeScoreMultiPlayer(scoreText, font);
	levelText = object.MakeLevelMultiPlayer(levelText, font);
	highScoreText = object.MakeHighScoreMultiPlayer(highScoreText, font);

	window.draw(background);
	window.draw(scoreText);
	window.draw(levelText);
	window.draw(highScoreText);

	gameBoard.SetWidthAndHight(10, 30);
	gameBoard.SetBoard(board);
	gameBoard.DrawBoard(m_gameover, cell, window);
	blockObject.DrawBlock(cx1, cy1, window, cell, piecePlayer1, nextPiecePlayer1, colorAssignedPlayer1, nextColorAssignedPlayer1);
	blockObject.DrawBlock(cx2, cy2, window, cell, piecePlayer2, nextPiecePlayer2, colorAssignedPlayer2, nextColorAssignedPlayer2);
	board = gameBoard.GetBoard<10, 30>();
}

void MultiPlayer::StartMultiPlayerGame()
{
	uint16_t nextColorAssigned, nextShapeAssigned, nextRotationAssigned;
	uint16_t coordX, coordY;
	uint16_t random;
	uint16_t score = 0, level = 1, increaseLevelUp = 5;
	uint16_t verify = 0;
	uint16_t nr = 0;
	int markerPlayAgain = 0;
	float timerSpeed = 1, delay = 0.6;
	bool existBlackHole = false, pieceTouchesBlackHole = false, pieceScaled = false;

	srand((unsigned)time(0));

	sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
	sf::RectangleShape shape(sf::Vector2f(cell_size, cell_size));

	graphics.ReadMusicPath();

	gameBoard.SetWidthAndHight(10, 30);
	board = gameBoard.GetBoard<10, 30>();

	/*SetCurrentPiece(piecePlayer1,colorAssignedPlayer1,shapeAssignedPlayer1,rotationAssignedPlayer1,cx1,cy1);
	SetCurrentPiece(piecePlayer2, colorAssignedPlayer2, shapeAssignedPlayer2, rotationAssignedPlayer2, cx2, cy2);
	SetNextPiece(nextPiecePlayer1,nextColorAssignedPlayer1,nextShapeAssignedPlayer1,nextRotationAssignedPlayer1,cx1,cy1);
	SetNextPiece(nextPiecePlayer2, nextColorAssignedPlayer2, nextShapeAssignedPlayer2, nextRotationAssignedPlayer2, cx2, cy2);*/

	sf::Clock clock;
	ReadImageAndFontPath();

	 //Crearea ferestrei pentru MultiPlayer
	sf::RenderWindow window2(sf::VideoMode(1000, 563), "Tetris Multiplayer");
	window2.create(sf::VideoMode(1000, 563), "Tetris Multiplayer");
	// Crearea imaginii ,sprite-ul si texture pt Multiplayer
	sf::Image imageMultiplayer;
	if(!imageTetrisPath.empty()) imageMultiplayer.loadFromFile(imageTetrisPath);
	sf::Texture textureMultiplayer;
	sf::Sprite spriteMultiplayer;
	textureMultiplayer.loadFromImage(imageMultiplayer);
	spriteMultiplayer.setTexture(textureMultiplayer);

	sf::Image imageGameOver;
	if(!imageGameOverPath.empty()) imageMultiplayer.loadFromFile(imageGameOverPath);
	sf::Texture textureGameOver;
	sf::Sprite spriteGameOver;
	textureGameOver.loadFromImage(imageGameOver);
	spriteGameOver.setTexture(textureGameOver);

	sf::Image imagePlayAgain;
	if (!imagePlayAgainPath.empty()) imagePlayAgain.loadFromFile(imagePlayAgainPath);

	sf::Texture texturePlayAgain;
	sf::Sprite spritePlayAgain;
	texturePlayAgain.loadFromImage(imagePlayAgain);
	spritePlayAgain.setTexture(texturePlayAgain);

	if (!fontPath.empty()) font.loadFromFile(fontPath);
	while (window2.isOpen())
	{
		//gameBoard.PlayMusicBackground();
		static float prev = clock.getElapsedTime().asSeconds();
		if (timerSpeed == level)
		{
			timerSpeed++;
			delay -= 0.1;
		}
		if (clock.getElapsedTime().asSeconds() - prev >= delay)
		{
			prev = clock.getElapsedTime().asSeconds();
			//Fall(piecePlayer1, nextPiecePlayer1, coordX, coordY, cx1, cy1, existBlackHole, pieceTouchesBlackHole, shapeAssignedPlayer1, colorAssignedPlayer1, nextColorAssignedPlayer1, nextRotationAssignedPlayer1, nextShapeAssignedPlayer1, rotationAssignedPlayer1);
			//Fall(piecePlayer2, nextPiecePlayer2, coordX, coordY, cx2, cy2, existBlackHole, pieceTouchesBlackHole, shapeAssignedPlayer2, colorAssignedPlayer2, nextColorAssignedPlayer2, nextRotationAssignedPlayer2, nextShapeAssignedPlayer2, rotationAssignedPlayer2);
		}

		sf::Event e;
		while (window2.pollEvent(e))
		{

			if (e.type == sf::Event::Closed)
			{
				graphics.StopMusicBackground();
				window2.close();

			}
			/*
			if (m_gameover == true && e.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f Mouse = window2.mapPixelToCoords(sf::Mouse::getPosition(window2));
				if (spritePlayAgain.getGlobalBounds().contains(Mouse))
					markerPlayAgain++;

			}
			if (shapeAssignedPlayer1 != 7)
			{
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Left)
					{
						cx1--;
						if (gameBoard.CheckBlock<10, 30>(piecePlayer1, cx1, cy1, pieceTouchesBlackHole) == false)
						{
							cx1++;
							graphics.PlayMusicWall();

						}
					}
					else if (e.key.code == sf::Keyboard::Right)
					{
						cx1++;
						if (gameBoard.CheckBlock<10, 30>(piecePlayer1, cx1, cy1, pieceTouchesBlackHole) == false)
						{
							cx1--;
							graphics.PlayMusicWall();

						}
					}

					else if (e.key.code == sf::Keyboard::M)
					{
						if (pieceTouchesBlackHole == false)
						{
							auxiliarPiecePlayer1 = piecePlayer1;
							piecePlayer1 = block.IncrasePiece(colorAssignedPlayer1, rotationAssignedPlayer1, shapeAssignedPlayer1);
							pieceScaled = true;
							if (gameBoard.CheckBlock<10, 30>(piecePlayer1, cx1, cy1, pieceTouchesBlackHole) == false)
							{
								piecePlayer1 = auxiliarPiecePlayer1;
								pieceScaled = false;
							}
						}

					}
					if (e.key.code == sf::Keyboard::N)
					{
						if (pieceTouchesBlackHole == false && pieceScaled == true)
						{
							piecePlayer1 = auxiliarPiecePlayer1;
							pieceScaled = false;
						}

					}

					else if (e.key.code == sf::Keyboard::Up)
					{
						auxiliarPiecePlayer1 = piecePlayer1;
						piecePlayer1 = block.RotateBlockAtCommand(piecePlayer1);
						if (gameBoard.CheckBlock<10, 30>(piecePlayer1, cx1, cy1, pieceTouchesBlackHole) == true)
						{
							graphics.PlayMusicRotate();
						}
						else
						{
							piecePlayer1 = auxiliarPiecePlayer1;
							graphics.PlayMusicWall();
						}
					}
				}

			}
			else if (shapeAssignedPlayer1 == 7)
			{
				if (e.type == sf::Event::KeyPressed)
				{
					if (e.key.code == sf::Keyboard::Left)
					{
						cx1--;
						if (gameBoard.CheckBlockForCell(piecePlayer1, cx1, cy1, pieceTouchesBlackHole) == false)
						{
							cx1++;
							graphics.PlayMusicWall();
						}
					}
					else if (e.key.code == sf::Keyboard::Right)
					{
						cx1++;
						if (gameBoard.CheckBlockForCell(piecePlayer1, cx1, cy1, pieceTouchesBlackHole) == false)
						{
							cx1--;
							graphics.PlayMusicWall();
						}
					}



				}

			}

			if (shapeAssignedPlayer2 != 7)
			{
				if (e.key.code == sf::Keyboard::A)
				{
					cx2--;
					if (gameBoard.CheckBlock<10, 30>(piecePlayer2, cx2, cy2, pieceTouchesBlackHole) == false)
					{
						cx2++;
						graphics.PlayMusicWall();

					}
				}
				else if (e.key.code == sf::Keyboard::D)
				{
					cx2++;
					if (gameBoard.CheckBlock<10, 30>(piecePlayer2, cx2, cy2, pieceTouchesBlackHole) == false)
					{
						cx2--;
						graphics.PlayMusicWall();

					}
				}

				else if (e.key.code == sf::Keyboard::X)
				{
					if (pieceTouchesBlackHole == false)
					{
						auxiliarPiecePlayer2 = piecePlayer2;
						piecePlayer2 = block.IncrasePiece(colorAssignedPlayer2, rotationAssignedPlayer2, shapeAssignedPlayer2);
						pieceScaled = true;
						if (gameBoard.CheckBlock<10, 30>(piecePlayer2, cx2, cy2, pieceTouchesBlackHole) == false)
						{
							piecePlayer2 = auxiliarPiecePlayer2;
							pieceScaled = false;
						}
					}

				}
				if (e.key.code == sf::Keyboard::Z)
				{
					if (pieceTouchesBlackHole == false && pieceScaled == true)
					{
						piecePlayer2 = auxiliarPiecePlayer2;
						pieceScaled = false;
					}

				}

				else if (e.key.code == sf::Keyboard::W)
				{
					auxiliarPiecePlayer2 = piecePlayer2;
					piecePlayer2 = block.RotateBlockAtCommand(piecePlayer2);
					if (gameBoard.CheckBlock<10, 30>(piecePlayer1, cx2, cy2, pieceTouchesBlackHole) == true)
					{
						graphics.PlayMusicRotate();
					}
					else
					{
						piecePlayer2 = auxiliarPiecePlayer1;
						graphics.PlayMusicWall();
					}
				}
			}
			else if (shapeAssignedPlayer2 == 7)
			{
				if (e.key.code == sf::Keyboard::A)
				{
					cx2--;
					if (gameBoard.CheckBlockForCell(piecePlayer2, cx2, cy2, pieceTouchesBlackHole) == false)
					{
						cx2++;
						graphics.PlayMusicWall();
					}
				}
				else if (e.key.code == sf::Keyboard::D)
				{
					cx2++;
					if (gameBoard.CheckBlockForCell(piecePlayer2, cx2, cy2, pieceTouchesBlackHole) == false)
					{
						cx2--;
						graphics.PlayMusicWall();
					}
				}
			}
		*/
		}
		//GenerateRandomBlackHole(existBlackHole, coordX, coordY, cell, window2);

		window2.clear();

		if (m_gameover == false)
		{
			DrawWindow(score, level, spriteMultiplayer, cell, window2);
			//window2.draw(spriteMultiplayer);
		}
		else
		{
			window2.draw(spriteGameOver);
			spritePlayAgain.setScale(0.80, 0.80);
			spritePlayAgain.setPosition(sf::Vector2f(90, 500));
			window2.draw(spritePlayAgain);
			if (markerPlayAgain != 0)
			{
				SetParametersForPlayAgain();
				window2.clear();
				break;
			}

		}

		window2.display();

	}


}

bool MultiPlayer::Fall(std::array<std::array<uint16_t, 4>, 4 > piece,std::array<std::array<uint16_t, 4>, 4 > nextPiece, uint16_t coordX,
	uint16_t coordY,int cx,int cy, bool existBlackHole,
	bool pieceTouchesBlackHole,uint16_t shapeAssigned,uint16_t colorAssigned,
	uint16_t nextColorAssigned,uint16_t nextRotationAssigned,uint16_t nextShapeAssigned ,uint16_t rotationAssigned)
{
	existBlackHole = false, pieceTouchesBlackHole=false;
	cy++;
	uint16_t condition = 0;
	for (uint16_t line = 0; line < 4; line++)
		for (uint16_t column = 0; column < 4; column++)
			if (piece[line][column] != 0)
			{
				condition++;
				break;
			}
	if (condition == 0)
	{
		DeleteBlackHole(existBlackHole, pieceTouchesBlackHole, coordY, coordX);
		gameBoard.SetBoard(board);
	}
	if (shapeAssigned != 7)
	{
		if (gameBoard.CheckBlock<10, 30>(piece, cx, cy, pieceTouchesBlackHole) == false || condition == 0)
		{

			FallPiece(piece,nextPiece,colorAssigned,shapeAssigned,rotationAssigned,nextColorAssigned, nextShapeAssigned, nextRotationAssigned,cx,cy);
			gameBoard.ClearLine(score, verify, level, increaseLevelUp, coordY);
			board = gameBoard.GetBoard<10, 30>();
			SetNextPiece(nextPiece,nextColorAssigned, nextShapeAssigned, nextRotationAssigned,cx,cy);
			SetCoordinates(cx1, cy1, cx2, cy2);
			nextPiece = blockObject.NewBlock(block, nextPiece);
			if (pieceTouchesBlackHole == true)
			{
				board[coordY][coordX] = 0;
				gameBoard.SetBoard(board);
				pieceTouchesBlackHole = false;
				existBlackHole = false;

			}

			return false;
		}

		return true;
	}
	else
	{
		if (gameBoard.CheckBlockForCell(piece, cx, cy, pieceTouchesBlackHole) == false || condition == 0)
		{
			FallPiece(piece, nextPiece, colorAssigned, shapeAssigned, rotationAssigned, nextColorAssigned, nextShapeAssigned, nextRotationAssigned, cx, cy);
			gameBoard.ClearLine(score, verify, level, increaseLevelUp, coordY);
			board = gameBoard.GetBoard<10, 30>();
			SetNextPiece(nextPiece, nextColorAssigned, nextShapeAssigned, nextRotationAssigned, cx, cy);
			SetCoordinates(cx1, cy1, cx2, cy2);
			nextPiece = blockObject.NewBlock(block, nextPiece);
			return false;
		}

		return true;
	}
}
void MultiPlayer::SetCurrentPiece(std::array<std::array<uint16_t, 4>, 4 >& piece,uint16_t &colorAssigned,uint16_t& shapeAssigned,uint16_t& rotationAssigned,int& cx,int& cy)
{
	RandomgenerateValues(colorAssigned, shapeAssigned, rotationAssigned);
	block.GetRandomRotation(rotationAssigned, colorAssigned, shapeAssigned, 0);
	SetCoordinates(cx1, cy1, cx2, cy2);
	piece = blockObject.NewBlock(block, piece);
}

void MultiPlayer::SetNextPiece(std::array<std::array<uint16_t, 4>, 4 >& nextPiece, uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, uint16_t& nextRotationAssigned, int& cx, int& cy)
{
	RandomgenerateValues(nextColorAssigned, nextShapeAssigned, nextRotationAssigned);
	block.GetRandomRotation(nextRotationAssigned, nextColorAssigned, nextShapeAssigned, 0);
	SetCoordinates(cx1, cy1, cx2, cy2);
	nextPiece = blockObject.NewBlock(block, nextPiece);
}

void MultiPlayer::SetCoordinates(int& cx1, int& cy1, int& cx2, int& cy2)
{
	cx1 = (width / 4), cx2 = width - (width / 4);
	cy1 = 0, cy2 = 0;
}