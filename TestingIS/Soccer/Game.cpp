#include "Game.h"

void Game::NotifyListenersOnWin() {
	for (const auto& weakListener : m_listeners) {
		if (auto listener = weakListener.lock()) {
			listener->OnWin();
		}
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

void Game::ResetGame() {
	m_playerObjects.clear();
	m_currentPlayer = EPlayer::PLAYER1;
	m_scorePlayerOne = 0;
	m_scorePlayerTwo = 0;
	m_listeners.clear();
}


void Game::UpdateScore(EPlayer scoredOn) {
	if (scoredOn == EPlayer::PLAYER1) {
		++m_scorePlayerTwo;
	}
	else if (scoredOn == EPlayer::PLAYER2) {
		++m_scorePlayerOne;
	}
}

EPlayer Game::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

std::vector<EPlayer> Game::GetPlayerObjects() const {
	return m_playerObjects;
}

void Game::AddListener(IGameListener* gameListener) {
	m_listeners.emplace_back(std::shared_ptr<IGameListener>(gameListener));
}


void Game::RemoveListener(IGameListener* gameListener) {
	m_listeners.erase(
		std::remove_if(m_listeners.begin(), m_listeners.end(),
			[gameListener](const std::weak_ptr<IGameListener>& weakPtr) {
				auto sp = weakPtr.lock();
				return !sp || sp.get() == gameListener;
			}),
		m_listeners.end());
}


std::shared_ptr<IGame> IGame::Produce()
{
	return std::make_shared<Game>();
}
