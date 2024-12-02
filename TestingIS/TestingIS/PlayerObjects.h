#pragma once

#include <vector>
#include "GameScene.h"


class PlayerObjects
{
private:
	std::vector<DraggableCircle*> m_players;
	DraggableCircle* m_ball;

	void Init(GameScene* gameScene);

public:
	PlayerObjects(GameScene* gameScene);
	void ResetPositions(GameScene* gameScene);
	DraggableCircle* GetBall();

};

