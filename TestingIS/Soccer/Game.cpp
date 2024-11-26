#include "Game.h"

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
		m_scorePlayerTwo;;
}

EPlayer Game::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

std::vector<EPlayer> Game::GetPlayerObjects() const
{
	return m_playerObjects;
}
