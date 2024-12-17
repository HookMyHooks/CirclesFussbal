// EasyMapStrategy.h
#pragma once
#include "IMapStrategy.h"
#include "ISquare.h"
#include "Square.h"
#include <vector>
#include <random>

class EasyMapStrategy : public IMapStrategy {
public:
    std::vector<std::vector<ISquare*>> GenerateMap(IPlayer* player1, IPlayer* player2) override;
};
