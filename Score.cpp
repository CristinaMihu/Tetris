#include "Score.h"
#include<sstream>
#include<fstream>

void Score::SetScore(int score)
{
	m_score = score;
}

void Score::SetLevel(int level)
{
	m_level = level;
}

void Score::checkHighScore(int score)
{
	if (m_highScore < score)
	{
		m_highScore = score;
		std::ofstream write("HighScore.txt");
		write << m_highScore;
	}

}

void Score::SetHighScore()
{
	std::ifstream read("HighScore.txt");
	if (read.is_open())
		read >> m_highScore;
	else "Error! ";
	read.close();
}

sf::Text Score::MakeScore(sf::Text& score, const sf::Font& font)
{
	
	std::stringstream string1;
	string1 << m_score;
	score.setString(string1.str().c_str());
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Black);
	score.setPosition(360., 134.);

	return score;

}

sf::Text Score::MakeLevel(sf::Text& level, const sf::Font& font)
{
	
	std::stringstream string2;
	string2 << m_level;
	level.setString(string2.str().c_str());
	level.setFont(font);
	level.setCharacterSize(35);
	level.setFillColor(sf::Color::Black);
	level.setPosition(360., 420.);
	

	return level;
}

sf::Text Score::MakeHighScore(sf::Text& highScore, const sf::Font& font)
{
	
	std::stringstream string3;
	string3 << m_highScore;
	highScore.setString(string3.str().c_str());
	highScore.setFont(font);
	highScore.setCharacterSize(30);
	highScore.setFillColor(sf::Color::Red);
	highScore.setPosition(360., 53.);
	
  
	return highScore;
}

sf::Text Score::MakeScoreMultiPlayer(sf::Text& score, const sf::Font& font)
{
	std::stringstream string1;
	string1 << m_score;
	score.setString(string1.str().c_str());
	score.setFont(font);
	score.setCharacterSize(35);
	score.setFillColor(sf::Color::Black);
	score.setPosition(870., 155.);

	return score;

}

sf::Text Score::MakeLevelMultiPlayer(sf::Text& level, const sf::Font& font)
{
	std::stringstream string2;
	string2 << m_level;
	level.setString(string2.str().c_str());
	level.setFont(font);
	level.setCharacterSize(35);
	level.setFillColor(sf::Color::Black);
	level.setPosition(870., 500.);


	return level;
}

sf::Text Score::MakeHighScoreMultiPlayer(sf::Text& highScore, const sf::Font& font)
{
	std::stringstream string3;
	string3 << m_highScore;
	highScore.setString(string3.str().c_str());
	highScore.setFont(font);
	highScore.setCharacterSize(35);
	highScore.setFillColor(sf::Color::Red);
	highScore.setPosition(870., 45.);


	return highScore;
}
