#pragma once

class IGameListener
{
public:
	virtual ~IGameListener() = default;
	virtual void OnWin() = 0;
};
