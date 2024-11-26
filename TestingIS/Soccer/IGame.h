#pragma once
#include "IGameListener.h"
class IGame
{
public:
	virtual std::vector<EPlayer> GetPlayerObjects() const = 0;
	virtual EPlayer GetCurrentPlayer() const = 0;
	//virtual void CheckForGoal(const float x, const float y) const = 0;
	static std::shared_ptr<IGame> Produce();

	virtual void AddListener(IGameListener* gameListener) = 0;
	virtual void RemoveListener(IGameListener* gameListener) = 0;

	

};

struct Post
{
	float x, y1, y2;
};