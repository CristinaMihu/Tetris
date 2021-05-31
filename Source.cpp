#include"Game.h"
#include"BoardSFML.h"
#include "../Logging/Logging.h"
#include"MultiPlayer.h"
#include<fstream>
void ReadImagesPath(std::string& imageMultiPlayerPath, std::string& imageSinglePlayerPath)
{
	std::ifstream read("ImagesForGame.txt");
	while (!read.eof())
	{
		read >> imageMultiPlayerPath;
		read >> imageSinglePlayerPath;
	}

}
void GameMethod()
{
	Game game;
	SFMLItems graphics;
	MultiPlayer multiPlayer;
	std::string imageMultiPlayerPath, imageSinglePlayerPath;
	ReadImagesPath(imageMultiPlayerPath, imageSinglePlayerPath);

	sf::RenderWindow windowBig;
	windowBig.create(sf::VideoMode(700, 600), "Tetris");
	sf::Image imageSinglePlayer, imageMultiPlayer;
	if(!imageSinglePlayerPath.empty()) imageSinglePlayer.loadFromFile(imageSinglePlayerPath);

	sf::Texture texture;
	sf::Sprite sprite;
	texture.loadFromImage(imageSinglePlayer);
	sprite.setTexture(texture);


	if (!imageMultiPlayerPath.empty()) imageMultiPlayer.loadFromFile(imageMultiPlayerPath);
	sf::Texture texture2;
	texture2.loadFromImage(imageMultiPlayer);
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);
	while (windowBig.isOpen())
	{

		sf::Event event;
		while (windowBig.pollEvent(event))
		{
			graphics.ReadMusicPath();
			graphics.PlayMusicBegin();
			if (event.type == sf::Event::Closed)
			{
				graphics.StopMusicBegin();
				windowBig.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				graphics.StopMusicBegin();
				game.StartGame();
				if (game.GetMemberGameOver()  !=false)
				{
					graphics.StopMusicBegin();
				}
				graphics.StopMusicBackground();
			}
			else 
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{

					multiPlayer.StartMultiPlayerGame();
				}
			}


			windowBig.clear(sf::Color::Black);
			sprite.setScale(0.65f, 0.65f);
			sprite2.setScale(0.65f, 0.65f);
			sprite.setPosition(sf::Vector2f(50, 50));
			sprite2.setPosition(sf::Vector2f(350, 50));
			windowBig.draw(sprite);
			windowBig.draw(sprite2);
			windowBig.display();
		}
	}

}
int main()
{
	Game game;

	Logging logger(std::cout);

	GameMethod();
	if (game.GetMemberPlayAgain() == true)
	{
		GameMethod();
	}
	else
	{
		logi("The game ended");
		logger.log("The game ended!", Logging::Level::Error);
	}
	return 0;
}