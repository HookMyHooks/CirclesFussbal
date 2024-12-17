#pragma once
#include "IMapStrategy.h"
#include "Square.h"
#include <vector>
#include <random>
class HardMapStrategy : public IMapStrategy
{
public:
	std::vector<std::vector<ISquare*>> GenerateMap(IPlayer* player1, IPlayer* player2) override;

};

