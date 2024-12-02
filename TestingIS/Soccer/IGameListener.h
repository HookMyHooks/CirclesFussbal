#pragma once

using IGameWeakPtr = std::weak_ptr<class IGameListener>;

class IGameListener
{
public:
	virtual ~IGameListener() = default;
	virtual void OnWin() = 0;


};
