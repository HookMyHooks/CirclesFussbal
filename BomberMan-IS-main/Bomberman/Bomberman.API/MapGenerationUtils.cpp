// MapGenerationUtils.cpp
#include "MapGenerationUtils.h"

namespace MapGenerationUtils {

    void GenerateRow(std::vector<ISquare*>& row, int line, int cols, int rows, const std::vector<std::pair<int, int>>& reservedPositions) {
        for (int col = 0; col < cols; col++) {
            ISquare* square = nullptr;

            // Unbreakable walls on the edges
            if (line == 0 || line == rows - 1 || col == 0 || col == cols - 1) {
                square = new Square(
                    { line, col },
                    nullptr,
                    ESquareType::UnbreakableWall,
                    Constants::WallUnbreakablePNGPath
                );
            }
            // Grass for reserved positions
            else if (IsReservedPosition(line, col, reservedPositions)) {
                square = new Square(
                    { line, col },
                    nullptr,
                    ESquareType::Grass,
                    Constants::GrassPNGPath
                );
            }
            // Randomly generate breakable walls or grass
            else {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> dis(0, 1);

                if (dis(gen) == 0) {
                    square = new Square(
                        { line, col },
                        nullptr,
                        ESquareType::Grass,
                        Constants::GrassPNGPath
                    );
                }
                else {
                    square = new Square(
                        { line, col },
                        nullptr,
                        ESquareType::Wall,
                        Constants::WallBreakablePNGPath
                    );
                }
            }

            row.push_back(square);
        }
    }

    bool IsReservedPosition(int line, int col, const std::vector<std::pair<int, int>>& reservedPositions) {
        for (const auto& pos : reservedPositions) {
            if (pos.first == line && pos.second == col) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::pair<int, int>> GetReservedPositions(int rows, int cols) {
        return {
            {rows - 2,cols - 2},       // Player 2 start position
            {rows - 2,cols - 3},      // Grass position near player 2
            {rows - 3,cols - 2},      // Grass position near player 2
            {1, 1},                     // Player 1 start position
            {1, 2},                     // Grass position near player 1
            {2, 1}                    // Grass position near player 1
        };
    }
}
