#pragma once
#include <iostream>
#include <vector>

#include "EPlayer.h"
#include "IGame.h"

class Game : public IGame
{
private:
	Post m_postOne, m_postTwo;

	std::pair<float, float> m_ballCoord;

	std::vector<EPlayer> m_playerObjects; // how many objects

	EPlayer m_currentPlayer;
	uint16_t m_scorePlayerOne;
	uint16_t m_scorePlayerTwo;
	
	std::vector<std::shared_ptr<IGameListener>> m_listeners; 


	


public:

	//Listeners
	void NotifyListenersOnWin() const;

	Game();

	void SwitchPlayers();
	//bool GoalScored(const float& x, const float& y);
	void ResetGame();
	void UpdateScore(EPlayer scoredOn);

	EPlayer GetCurrentPlayer() const override;
	std::vector<EPlayer> GetPlayerObjects() const override;


	void AddListener(IGameListener* gameListener) override;
	void RemoveListener(IGameListener* gameListener) override;

};

