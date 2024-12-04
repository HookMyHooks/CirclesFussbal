#pragma once
#include "IGameListener.h"
#include "Map.h"
#include <tuple>
class IGame
{
public:
	virtual ~IGame() = default;

	virtual IMap* getMap() = 0;
	virtual bool isOver() = 0;
	virtual void SetGameOver() = 0;
	virtual void MovePlayer(IPlayer* player, EPlayerMovementType movementDir) = 0;
	virtual IPlayer* GetPlayer1() = 0;
	virtual IPlayer* GetPlayer2() = 0;
	virtual float GetGameTimer() = 0;
	virtual void PlaceBomb(IPlayer* player) = 0;
	virtual void HandleExplosion(float elapsedTime) = 0;
	virtual void HandleActiveFire(const float& elapsedTime) = 0;
	virtual bool addGameListener(IGameListener* listener) = 0;
	virtual bool removeGameListener(IGameListener* listener) = 0;
	virtual void notifyAllListeners() = 0;
	virtual void UpdateTimer(float elapsedTimer) = 0;
};

