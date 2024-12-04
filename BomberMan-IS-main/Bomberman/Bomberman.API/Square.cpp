#include "Square.h"
#include <iostream>

Square::Square(std::pair<int, int> pos, IPlayer* player, ESquareType squareType, std::string imagePath): bomb(nullptr), fire(nullptr)
{
    this->position = pos;
    this->player = player;
    this->squareType = squareType;

    if (Constants::isValidPath(imagePath)) {
        this->imagePath = imagePath;
    }
    else {
        std::cerr << "Image does not exist: " << imagePath << std::endl;
    }
}

std::pair<int, int> Square::GetPosition() const
{
    return position;
}

bool Square::HasPlayer() const
{
    if (player != nullptr)
    {
        return true;
    }
    return false;
}

ESquareType Square::GetSquareType() const
{
    return squareType;
}

IPlayer* Square::GetPlayer() const
{
    return player;
}

IBomb* Square::GetBomb() const
{
    return bomb;
}

IFire* Square::GetFire() const
{
    return fire;
}

std::string Square::GetImagePath() const
{
    return imagePath;
}

void Square::SetPlayer(IPlayer* player)
{
    this->player = player;
    this->player->SetPosition(this->position.first,this->position.second);
}

void Square::SetBomb(IBomb* bomb)
{
    this->bomb = bomb;
}

void Square::SetFire(IFire* fire)
{
    this->fire = fire;
}


void Square::SetImagePath(std::string imagePath)
{
    this->imagePath = imagePath;
}

void Square::SetSquareType(ESquareType squareType)
{
    this->squareType = squareType;
}

void Square::RemovePlayer()
{
    player = nullptr;
}

void Square::ClearBomb()
{
    if (bomb)
    {
        delete bomb;
        bomb = nullptr;
    }
}

void Square::ClearFire()
{
    if (fire)
    {
        delete fire;
        fire = nullptr;
    }
}


bool Square::HasWall() const
{
    return squareType == ESquareType::Grass;
}

bool Square::HasBomb() const
{
    return bomb != nullptr;
}

bool Square::HasFire() const
{
    return fire != nullptr;
}

bool Square::HasBombExploded() const
{
    return this->bomb->HasExploded();
}


