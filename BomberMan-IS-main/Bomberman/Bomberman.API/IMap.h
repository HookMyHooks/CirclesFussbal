#pragma once
#pragma once
#include <vector>
#include <string>
#include <utility>
#include "Square.h"


class IMap {
public:
    virtual void Initialize(IPlayer* player1, IPlayer* player2) = 0;
    virtual void ResetMap() = 0;
    virtual std::pair<int, int> GetMapDimensions() const = 0;
    virtual std::vector<std::vector<ISquare*>> getBoard() const = 0;
    virtual ISquare* GetSquare(int x, int y) const = 0;
    virtual bool HasBombOnSquare(std::pair<int, int> position) const = 0;
    virtual void PlaceBomb(int x, int y) = 0;
    virtual void LoadFromFile(std::string filePath, IPlayer* player1, IPlayer* player2) = 0;
    virtual ~IMap() = default;
};

