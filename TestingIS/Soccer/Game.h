#pragma once
#include <iostream>
#include <vector>

#include "EPlayer.h"
#include "IGame.h"
#include "IGameListener.h"
class Game : public IGame
{
private:
	Post m_postOne, m_postTwo;

	std::pair<float, float> m_ballCoord;

	std::vector<EPlayer> m_playerObjects; // how many objects

	EPlayer m_currentPlayer;
	uint16_t m_scorePlayerOne;
	uint16_t m_scorePlayerTwo;
	
	std::vector<std::weak_ptr<IGameListener>> m_listeners;

	
	


public:

	Game();

	void SwitchPlayers() override;
	void ResetGame() override;
	void UpdateScore(EPlayer scoredOn) override;

	EPlayer GetCurrentPlayer() const override;
	std::vector<EPlayer> GetPlayerObjects() const override;

	void AddListener(IGameListener* gameListener) override;
	void RemoveListener(IGameListener* gameListener) override;

	void NotifyListenersOnWin() override;

};

