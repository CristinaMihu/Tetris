#include "SFMLItems.h"
#include<fstream>

void SFMLItems::ReadMusicPath()
{
	std::ifstream readMusic("MusicPath.txt");

	while (!readMusic.eof())
	{
		readMusic >> musicBackgroundPath;
		readMusic >> musicDeleteLinePath;
		readMusic >> musicWallPath;
		readMusic >> musicGameOverPath;
		readMusic >> musicBlackHolePath;
		readMusic >> musicVanishPath;
		readMusic >> musicRotatePath;
		readMusic >> musicBeginPath;
	}

	readMusic.close();
}

void SFMLItems::PlayMusicBackground()
{
	if (!musicBackgroundPath.empty() && musicBackground.openFromFile(musicBackgroundPath))
		musicBackground.play();
}

void SFMLItems::PlayMusicDeleteLine()
{
	if (!musicDeleteLinePath.empty() && musicDeleteLine.openFromFile(musicDeleteLinePath))
		musicDeleteLine.play();
}

void SFMLItems::PlayMusicWall()
{
	if (!musicWallPath.empty() && musicWall.openFromFile(musicWallPath))
		musicWall.play();
}

void SFMLItems::PlayMusicGameOver()
{
	if (!musicGameOverPath.empty() && musicGameOver.openFromFile(musicGameOverPath))
		musicGameOver.play();
}

void SFMLItems::PlayMusicBlackHole()
{
	if (!musicBlackHolePath.empty() && musicBlackHole.openFromFile(musicBlackHolePath))
		musicBlackHole.play();
}

void SFMLItems::PlayMusicVanish()
{
	if (!musicVanishPath.empty() && musicVanish.openFromFile(musicVanishPath))
		musicVanish.play();
}

void SFMLItems::PlayMusicRotate()
{
	if (!musicRotatePath.empty() && musicRotate.openFromFile(musicRotatePath))
		musicRotate.play();
}

void SFMLItems::PlayMusicBegin()
{
	if (!musicBeginPath.empty() && musicBegin.openFromFile(musicBeginPath))
		musicBegin.play();
}

void SFMLItems::StopMusicBackground()
{
	musicBackground.stop();
}

void SFMLItems::StopMusicBegin()
{
	musicBegin.stop();
}


