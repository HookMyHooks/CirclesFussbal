#pragma once
#include "IPlayerListener.h"

class PlayerListener : public IPlayerListener
{
public:
    virtual void OnPlayerMoved(int newX, int newY);
    virtual void OnPlayerPlacedBomb(int x, int y);
    virtual void OnPlayerDestroyed();
};
