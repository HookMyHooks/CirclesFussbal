#pragma once
#include "IMap.h"
#include <random>
#include "EMapInitialization.h"
#include "IMapStrategy.h"

class Map : public IMap
{
private:
	std::vector<std::vector<ISquare*>> board;
	IMapStrategy* strategy;

public:
	Map(IPlayer* player1 , IPlayer* player2, IMapStrategy* strategy);

	void Initialize(IPlayer* player1, IPlayer* player2) override;
	void ResetMap() override;
	std::pair<int, int> GetMapDimensions() const override;
	std::vector<std::vector<ISquare*>> getBoard() const override;
	ISquare* GetSquare(int x, int y) const override;

	bool HasBombOnSquare(std::pair<int, int> position) const override;
	void PlaceBomb(int x, int y) override;
	void LoadFromFile(std::string filePath, IPlayer* player1, IPlayer* player2) override;

};

