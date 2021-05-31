#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class SFMLItems
{
public:
	void ReadMusicPath();
	void PlayMusicBackground();
	void PlayMusicDeleteLine();
	void PlayMusicWall();
	void PlayMusicGameOver();
	void PlayMusicBlackHole();
	void PlayMusicVanish();
	void PlayMusicRotate();
	void PlayMusicBegin();
	void StopMusicBackground();
	void StopMusicBegin();



private:
	sf::Music musicBackground, musicDeleteLine, musicWall, musicGameOver, musicBlackHole, musicVanish, musicRotate, musicBegin;

private:
	std::string  musicBackgroundPath, musicDeleteLinePath, musicWallPath,
		musicGameOverPath, musicBlackHolePath, musicVanishPath, musicRotatePath, musicBeginPath;
};

