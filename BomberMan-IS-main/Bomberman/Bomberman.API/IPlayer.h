#pragma once
#include <utility>
#include <string>
#include <vector>
#include "EPlayerType.h"
#include "EPlayerMovementType.h"
#include <chrono>
#include "Constants.h"

class IPlayer {
public:
    virtual ~IPlayer() = default;
    virtual std::pair<int, int> GetPosition() const = 0;
    virtual bool HasPlacedBomb() const = 0;
    virtual std::string GetImagePath() const = 0;
    virtual void SetPosition(int x, int y) = 0;
    virtual void StatePlaceBomb() = 0;
    virtual void SetImagePath(const std::string& path) = 0;
    virtual void SetLastMoveTime(const std::chrono::steady_clock::time_point& newTime) = 0;
    virtual bool CanMove() = 0;
};