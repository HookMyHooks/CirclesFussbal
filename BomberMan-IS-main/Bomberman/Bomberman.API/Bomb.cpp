#include "Bomb.h"

Bomb::Bomb(std::pair<int, int> position, int range,float timer): position(position), range(range), timer(timer)
{
	imagePath = Constants::BombPNGPath;
	if (!Constants::isValidPath(imagePath)) {
		std::cerr << "Image does not exist: " << imagePath << std::endl;
	}
}

std::pair<int, int> Bomb::GetPosition() const
{
	return position;
}

int Bomb::GetRange() const
{
	return range;
}


std::string Bomb::GetImagePath() const
{
	return imagePath;
}

void Bomb::SetImagePath(const std::string& path)
{
	imagePath = path;
}

bool Bomb::HasExploded() const
{
	return timer <= 0;
}

void Bomb::UpdateTimer(float elapsedTime)
{
	timer -= elapsedTime;

}