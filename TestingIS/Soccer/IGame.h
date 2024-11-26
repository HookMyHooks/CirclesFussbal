#pragma once

class IGame
{
public:
	virtual void GetPlayerObject() const = 0;
	virtual void GetCurrentPlayer() const = 0;
	virtual void CheckForGoal(const float x, const float y) const = 0;
};

struct Post
{
	float x, y1, y2;
};