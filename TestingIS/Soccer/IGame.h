#pragma once

class IGame
{
public:
	virtual std::vector<EPlayer> GetPlayerObjects() const = 0;
	virtual EPlayer GetCurrentPlayer() const = 0;
	//virtual void CheckForGoal(const float x, const float y) const = 0;
};

struct Post
{
	float x, y1, y2;
};