#include "PlayerObjects.h"

PlayerObjects::PlayerObjects(GameScene* gameScene)
{

#pragma region PlayersDeclaration
	//Red Team
	//Def
	DraggableCircle* redDef1= new DraggableCircle( -80, -160, 60, false);
	DraggableCircle* redDef2 = new DraggableCircle(-80, 240, 60 , false);
	DraggableCircle* redDef3 = new DraggableCircle(-80, 40, 60  , false);
	redDef1->setColor(Qt::red);
	redDef2->setColor(Qt::red);
	redDef3->setColor(Qt::red);
	m_players.emplace_back(redDef1);
	m_players.emplace_back(redDef2);
	m_players.emplace_back(redDef3);
	//Att
	DraggableCircle* redAtt1 = new DraggableCircle(120, -80, 60, false);
	DraggableCircle* redAtt2 = new DraggableCircle(120, 160, 60, false);
	redAtt1->setColor(Qt::red);
	redAtt2->setColor(Qt::red);
	m_players.emplace_back(redAtt1);
	m_players.emplace_back(redAtt2);


	//Blue Team
	//Def
	DraggableCircle* blueAtt1 = new DraggableCircle(450, 160, 60, false);
	DraggableCircle* blueAtt2 = new DraggableCircle(450, -80, 60, false);
	blueAtt1->setColor(Qt::blue);
	blueAtt2->setColor(Qt::blue);
	m_players.emplace_back(blueAtt1);
	m_players.emplace_back(blueAtt2);
	//Att
	DraggableCircle* blueDef1 = new DraggableCircle(620, -180, 60, false);
	DraggableCircle* blueDef2 = new DraggableCircle(620, 40, 60 , false);
	DraggableCircle* blueDef3 = new DraggableCircle(620, 240, 60 , false);
	blueDef1->setColor(Qt::blue);
	blueDef2->setColor(Qt::blue);
	blueDef3->setColor(Qt::blue);
	m_players.emplace_back(blueDef1);
	m_players.emplace_back(blueDef2);
	m_players.emplace_back(blueDef3);
#pragma endregion

	//ball
	m_ball = new DraggableCircle(279, 79, 50,true);
	

	for (size_t i = 0; i < m_players.size(); i++)
	{
		gameScene->addItem(m_players[i]);
		gameScene->addItem(m_ball);
	}
}

DraggableCircle* PlayerObjects::GetBall()
{
	return m_ball;
}
