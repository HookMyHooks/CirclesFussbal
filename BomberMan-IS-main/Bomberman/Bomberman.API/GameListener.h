#pragma once
#include "IGameListener.h"
#include <iostream>

class GameListener : public IGameListener
{
	void GameListener::OnPlayerMoved(int x, int y)
	{
		std::cout << "You moved the player." << std::endl;
	}

	void GameListener::OnPlayerPlacedBomb(int x, int y)
	{
		std::cout << "You placed a bomb." << std::endl;
	}

	void GameListener::OnPlayerDestroyed()
	{
		std::cout << "Player destroyed." << std::endl;
	}
};

