#pragma once

#include <vector>
#include "GameScene.h"


class PlayerObjects
{
private:
	std::vector<DraggableCircle*> m_players;
	DraggableCircle* m_ball;

public:
	PlayerObjects(GameScene* gameScene);
	void ResetPositions();
};

