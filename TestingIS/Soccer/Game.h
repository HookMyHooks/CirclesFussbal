#pragma once
#include <iostream>
//#include "EPlayer.h"
class Game
{
private: 
	std::pair<float, float> m_postOne;
	std::pair<float, float> m_postTwo;
	std::pair<float, float> m_ballCoord;
	//std::vector<EPlayer> m_playerObject;
	//EPlayer m_currentPlayer;
	uint16_t m_scorePlayerOne;
	uint16_t m_scorePlayerTwo;


public:
	void SwitchPlayers();
	bool GoalScored(const float& x, const float& y);
	void ResetPositions();
	void InitiatePlayerObjects();
	void UpdateScore(); //EPlayer scoredOn



};

