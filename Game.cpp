#include"Game.h"
#include<iostream>
#include<fstream>
#include <random>
#include <ctime>
using namespace sf;


void Game::SetBoard(std::array<std::array<uint16_t, 10>, 20> board)
{
	this->board = board;
}

void Game::SetCurrentPiece()
{
	RandomgenerateValues(colorAssigned, shapeAssigned, rotationAssigned);
	block.GetRandomRotation(rotationAssigned, colorAssigned, shapeAssigned, 0);
	SetCoordinates(cx, cy);
	piece = blockObject.NewBlock(block, piece);
	
}

void Game::SetNextPiece(uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, uint16_t& nextRotationAssigned)
{
	RandomgenerateValues(nextColorAssigned, nextShapeAssigned, nextRotationAssigned);
	block.GetRandomRotation(nextRotationAssigned, nextColorAssigned, nextShapeAssigned, 0);
	SetCoordinates(cx, cy);
	nextPiece = blockObject.NewBlock(block, nextPiece);
}

void Game::SetParametersForPlayAgain()
{
	this->m_gameover = false;
	this->board = { 0 };
	this->piece = { 0 };
	this->nextPiece = { 0 };
	this->auxiliarPiece = { 0 };
	this->aux = { 0 };
	this->m_playAgain = true;
	gameBoard.SetBoard(board);

}


void Game::ReadImageAndFontPath()
{
	std::ifstream readImage("ImagePath.txt");

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
const int height = 19;



void Game::RandomgenerateValues(uint16_t& colorAssigned, uint16_t& shapeAssigned, uint16_t& rotationAssigned)
{
	colorAssigned = rand() % 6;
	shapeAssigned = rand() % 8;
	rotationAssigned = rand() % 4;
}

void Game::FallPiece(uint16_t& nextColorAssigned, uint16_t& nextShapeAssigned, uint16_t& nextRotationAssigned)
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

void Game::DeleteBlackHole(bool& existBlackHole, bool& pieceTouchesBlackHole, uint16_t coordY, uint16_t coordX)
{
	board[coordY][coordX] = 0;
	gameBoard.SetBoard(board);
	existBlackHole = false;
	pieceTouchesBlackHole = false;
}

void Game::GenerateRandomBlackHole(bool& existBlackHole, uint16_t& coordX, uint16_t& coordY, RectangleShape cell, sf::RenderWindow& window)
{
	uint16_t	random = rand() % 10000;
	if (random == 7 && m_gameover == false && existBlackHole == false)
	{
		coordX = rand() % width;
		coordY = rand() % height;
		existBlackHole = true;
		if (coordY == 0 || coordY==1 || coordY==2)
			coordY += 3;
		if (board[coordY][coordX] != 0)
		{
			board[coordY][coordX] = 0;
			SetBoard(board);
			existBlackHole = false;
			graphics.PlayMusicVanish();
			cell.setFillColor(Color::Red);
			cell.setOutlineColor(Color::Black);
			cell.setOutlineThickness(1.f);
			cell.setPosition(Vector2f(coordX * cell_size, coordY * cell_size));
			window.draw(cell);
		}
		else
		{

			board[coordY][coordX] = 10;
			graphics.PlayMusicBlackHole();

		}
	}
}

void Game::DrawWindow(uint16_t score, uint16_t level, uint16_t nextColorAssigned, Sprite background, RectangleShape cell, sf::RenderWindow& window)
{
	object.SetScore(score);
	object.SetLevel(level);
	object.SetHighScore();
	object.checkHighScore(score);
	scoreText = object.MakeScore(scoreText, font);
	levelText = object.MakeLevel(levelText, font);
	highScoreText = object.MakeHighScore(highScoreText, font);

	window.draw(background);
	window.draw(scoreText);
	window.draw(levelText);
	window.draw(highScoreText);

	gameBoard.SetWidthAndHight(10, 19);
	gameBoard.SetBoard(board);
	gameBoard.DrawBoard(m_gameover, cell, window);
	blockObject.DrawBlock(cx, cy, window, cell, piece, nextPiece, colorAssigned, nextColorAssigned);
	board = gameBoard.GetBoard<10, 20>();
}


void Game::StartGame()
{

	uint16_t nextColorAssigned, nextShapeAssigned, nextRotationAssigned;
	uint16_t coordX, coordY;
	uint16_t random;
	uint16_t score = 0, level = 1, increaseLevelUp = 10;
	uint16_t verify = 0;
	uint16_t nr = 0;
	int markerPlayAgain = 0;

	float timerSpeed = 1, delay = 0.6;

	bool existBlackHole = false, pieceTouchesBlackHole = false, pieceScaled = false;

	srand((unsigned)time(0));

	RectangleShape cell(Vector2f(cell_size, cell_size));
	RectangleShape shape(Vector2f(cell_size, cell_size));

	ReadImageAndFontPath();
	if (!fontPath.empty()) font.loadFromFile(fontPath);
	if (!imageTetrisPath.empty()) imageTexture.loadFromFile(imageTetrisPath);
	if (!imageGameOverPath.empty()) tGameOver.loadFromFile(imageGameOverPath);

	sf::Image imagePlayAgain;
	if (!imagePlayAgainPath.empty()) imagePlayAgain.loadFromFile(imagePlayAgainPath);

	sf::Texture texturePlayAgain;
	sf::Sprite spritePlayAgain;
	texturePlayAgain.loadFromImage(imagePlayAgain);
	spritePlayAgain.setTexture(texturePlayAgain);

	Sprite background(imageTexture);
	Sprite backgroundGameOver(tGameOver);

	backgroundGameOver.setScale(0.8f, 0.9f);
	backgroundGameOver.setPosition(0.0f, 30.0f);

	graphics.ReadMusicPath();
	graphics.PlayMusicBackground();
	blockObject.SetWidth(width);
	blockObject.SetCellSize();
	gameBoard.SetWidthAndHight(10, 19);
	board =gameBoard.GetBoard<10, 20>();

	SetCurrentPiece();
	SetNextPiece(nextColorAssigned, nextShapeAssigned, nextRotationAssigned);

	Clock clock;

	auto fall = [&]()
	{
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
			if (gameBoard.CheckBlock<10, 20>(piece, cx, cy, pieceTouchesBlackHole) == false || condition == 0)
			{

				FallPiece(nextColorAssigned, nextShapeAssigned, nextRotationAssigned);
				gameBoard.ClearLine(score, verify, level, increaseLevelUp, coordY);
				board = gameBoard.GetBoard<10, 20>();
				SetNextPiece( nextColorAssigned, nextShapeAssigned, nextRotationAssigned);
				SetCoordinates(cx, cy);
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
				FallPiece(nextColorAssigned, nextShapeAssigned, nextRotationAssigned);
				gameBoard.ClearLine(score, verify, level, increaseLevelUp, coordY);
				board = gameBoard.GetBoard<10, 20>();
				SetNextPiece( nextColorAssigned, nextShapeAssigned, nextRotationAssigned);
				SetCoordinates(cx, cy);
				nextPiece = blockObject.NewBlock(block, nextPiece);
				return false;
			}

			return true;
		}
	};
	sf::RenderWindow window(sf::VideoMode(500, 600), "Tetris Single Player");
	while (window.isOpen())
	{
		
		static float prev = clock.getElapsedTime().asSeconds();
		if (timerSpeed == level)
		{
			timerSpeed++;
			delay -= 0.1;
		}
		if (clock.getElapsedTime().asSeconds() - prev >= delay)
		{
			prev = clock.getElapsedTime().asSeconds();
			fall();
		}

		Event e;
		while (window.pollEvent(e))
		{

			if (e.type == sf::Event::Closed)
			{
				graphics.StopMusicBackground();
				window.close();

			}
			if (m_gameover == true && e.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f Mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if (spritePlayAgain.getGlobalBounds().contains(Mouse))
					markerPlayAgain++;

			}
			if (shapeAssigned != 7)
			{
				if (e.type == Event::KeyPressed)
				{
					if (e.key.code == Keyboard::Left)
					{
						cx--;
						if (gameBoard.CheckBlock<10, 20>(piece, cx, cy, pieceTouchesBlackHole) == false)
						{
							cx++;
							graphics.PlayMusicWall();

						}
					}
					else if (e.key.code == Keyboard::Right)
					{
						cx++;
						if (gameBoard.CheckBlock<10, 20>(piece, cx, cy, pieceTouchesBlackHole) == false)
						{
							cx--;
							graphics.PlayMusicWall();

						}
					}
					else if (e.key.code == Keyboard::Down)
					{
						cy++;
						if (gameBoard.CheckBlock<10, 20>(piece, cx, cy, pieceTouchesBlackHole) == false)
						{
							cy--;
						}
						else
						{
							fall();
						}
					}
					else if (e.key.code == Keyboard::X)
					{
						if (pieceTouchesBlackHole == false)
						{
							auxiliarPiece = piece;
							piece = block.IncrasePiece(colorAssigned, rotationAssigned, shapeAssigned);
							pieceScaled = true;
							if (gameBoard.CheckBlock<10, 20>(piece, cx, cy, pieceTouchesBlackHole) == false)
							{
								piece = auxiliarPiece;
								pieceScaled = false;
							}
						}

					}
					if (e.key.code == Keyboard::Z)
					{
						if (pieceTouchesBlackHole == false && pieceScaled == true)
						{
							piece = auxiliarPiece;
							pieceScaled = false;
						}

					}

					else if (e.key.code == Keyboard::Up)
					{
						aux = piece;
						piece = block.RotateBlockAtCommand(piece);
						if (gameBoard.CheckBlock<10, 20>(piece, cx, cy, pieceTouchesBlackHole) == true)
						{
							graphics.PlayMusicRotate();
						}
						else
						{
							piece = aux;
							graphics.PlayMusicWall();
						}
					}
				}

			}
			else
			{
				if (e.type == Event::KeyPressed)
				{
					if (e.key.code == Keyboard::Left)
					{
						cx--;
						if (gameBoard.CheckBlockForCell(piece, cx, cy, pieceTouchesBlackHole) == false)
						{
							cx++;
							graphics.PlayMusicWall();
						}
					}
					else if (e.key.code == Keyboard::Right)
					{
						cx++;
						if (gameBoard.CheckBlockForCell(piece, cx, cy, pieceTouchesBlackHole) == false)
						{
							cx--;
							graphics.PlayMusicWall();
						}
					}
					else if (e.key.code == Keyboard::Down)
					{
						cy++;
						if (gameBoard.CheckBlockForCell(piece, cx, cy, pieceTouchesBlackHole) == false)
						{
							cy--;
						}
						else
						{
							fall();
						}
					}

				}

			}
		}

		GenerateRandomBlackHole( existBlackHole, coordX, coordY, cell, window);

		window.clear();



		if (m_gameover == false)
		{
			DrawWindow( score, level, nextColorAssigned, background, cell, window);
		}
		else
		{
			clock.restart();
			prev = clock.getElapsedTime().asSeconds();
			window.draw(backgroundGameOver);
			graphics.StopMusicBackground();
			spritePlayAgain.setScale(0.80, 0.80);
			spritePlayAgain.setPosition(sf::Vector2f(90, 500));
			window.draw(spritePlayAgain);
			if (markerPlayAgain != 0)
			{
				SetParametersForPlayAgain();
				window.clear();
				break;
			}

		}

		window.display();

	}


}

bool Game::IsSpriteHover(sf::FloatRect sprite, sf::Vector2f mp)
{
	if (sprite.contains(mp))
	{
		return true;
	}
	return false;
}

bool Game::GetMemberGameOver()
{
	return m_gameover;
}


bool Game::GetMemberPlayAgain()
{
	return m_playAgain;
}

void Game::SetCoordinates(int& cx, int& cy)
{
	cx = (width / 2) - 2, cy = 0;
}


