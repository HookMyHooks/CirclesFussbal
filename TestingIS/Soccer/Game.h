#pragma once
#include <iostream>
#include <vector>

#include "EPlayer.h"
#include "IGame.h"

class Game : IGame
{
private:
	Post m_postOne, m_postTwo;

	std::pair<float, float> m_ballCoord;

	std::vector<EPlayer> m_playerObjects; // how many objects

	EPlayer m_currentPlayer;
	uint16_t m_scorePlayerOne;
	uint16_t m_scorePlayerTwo;


public:

	Game();

	void SwitchPlayers();
	//bool GoalScored(const float& x, const float& y);
	void ResetGame();
	void UpdateScore(EPlayer scoredOn); //EPlayer scoredOn

	EPlayer GetCurrentPlayer() const override;
	std::vector<EPlayer> GetPlayerObjects() const override;
};

