// MapGenerationUtils.h
#pragma once
#include <vector>
#include "ISquare.h"
#include "Square.h"
#include "Constants.h"
#include <random>

namespace MapGenerationUtils {
    void GenerateRow(std::vector<ISquare*>& row, int line, int cols, int rows, const std::vector<std::pair<int, int>>& reservedPositions);
    bool IsReservedPosition(int line, int col, const std::vector<std::pair<int, int>>& reservedPositions);

    std::vector<std::pair<int, int>> GetReservedPositions(int rows, int cols);
}
