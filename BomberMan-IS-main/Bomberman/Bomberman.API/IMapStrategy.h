// IMapStrategy.h
#pragma once
#include <vector>
#include "ISquare.h"
#include "IPlayer.h"

class IMapStrategy {
public:
    virtual ~IMapStrategy() = default;
    virtual std::vector<std::vector<ISquare*>> GenerateMap(IPlayer* player1, IPlayer* player2) = 0;

protected:
    int rows, collumns;
};
