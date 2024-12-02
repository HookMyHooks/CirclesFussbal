#include "Game.h"

void Game::NotifyListenersOnWin() const
{
	for (auto it : m_listeners)
	{
		it->OnWin();
	}
}

Game::Game()
{
	m_currentPlayer = EPlayer::PLAYER1;
	m_scorePlayerOne = m_scorePlayerTwo = 0;
}

void Game::SwitchPlayers()
{
	if (m_currentPlayer == EPlayer::PLAYER1)
		m_currentPlayer = EPlayer::PLAYER2;
	else
		m_currentPlayer = EPlayer::PLAYER1;
}

//bool Game::GoalScored(const float& x, const float& y)
//{
//	if (x < 0)
//	{
//		if (y < m_postOne.y1 && y > m_postOne.y2) m_scorePlayerTwo++;
//	}
//}

void Game::ResetGame()
{
	m_currentPlayer = EPlayer::PLAYER1;
	m_scorePlayerOne = m_scorePlayerTwo = 0;
}


void Game::UpdateScore(EPlayer scoredOn)
{
	if (scoredOn == EPlayer::PLAYER1)
		m_scorePlayerTwo++;
	else
		m_scorePlayerOne++;
}

EPlayer Game::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

std::vector<EPlayer> Game::GetPlayerObjects() const
{
	return m_playerObjects;
}

void Game::AddListener(IGameListener* gameListener)
{
	m_listeners.emplace_back(gameListener);
}


void Game::RemoveListener(IGameListener* gameListener)
{
	auto func = [gameListener](IGameWeakPtr el)
		{
			auto sp = el.lock();
			return !sp || gameListener == sp.get();
		};
	m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), func));
}


std::shared_ptr<IGame> IGame::Produce()
{
	return std::make_shared<Game>();
}
