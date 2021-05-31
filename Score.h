#pragma once
#include <SFML/Graphics.hpp>


class Score  {

public:
    
    void SetScore(int score);
    void SetLevel(int level);
    void checkHighScore(int score);
    void SetHighScore();

    sf::Text MakeScore(sf::Text& score,const sf::Font& font );
    sf::Text MakeLevel(sf::Text& level, const sf::Font& font);
    sf::Text MakeHighScore(sf::Text& highScore, const sf::Font& font);

    sf::Text MakeScoreMultiPlayer(sf::Text& score, const sf::Font& font);
    sf::Text MakeLevelMultiPlayer(sf::Text& level, const sf::Font& font);
    sf::Text MakeHighScoreMultiPlayer(sf::Text& highScore, const sf::Font& font);

private:
    int m_score;
    int m_highScore;
    int m_level;
};

