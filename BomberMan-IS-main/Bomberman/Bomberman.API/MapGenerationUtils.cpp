// MapGenerationUtils.cpp
#include "MapGenerationUtils.h"

namespace MapGenerationUtils {

    /**
     * @brief Generates a row of the game map with appropriate square types.
     *
     * Creates squares based on their position within the row and the map, assigning
     * unbreakable walls, grass, or randomly generating breakable walls or grass for
     * each position. Reserved positions are always grass.
     *
     * @param row A reference to the vector representing the row to be generated.
     * @param line The current row index in the map grid.
     * @param cols The total number of columns in the map.
     * @param rows The total number of rows in the map.
     * @param reservedPositions A vector of positions that should always be grass.
     */
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

    /**
     * @brief Checks if a given position is reserved.
     *
     * Determines if a specific map position belongs to the list of reserved positions,
     * which are used for ensuring specific areas (like player starting positions) are always grass.
     *
     * @param line The row index of the position to check.
     * @param col The column index of the position to check.
     * @param reservedPositions A vector of reserved positions.
     * @return True if the position is reserved, false otherwise.
     */
    bool IsReservedPosition(int line, int col, const std::vector<std::pair<int, int>>& reservedPositions) {
        for (const auto& pos : reservedPositions) {
            if (pos.first == line && pos.second == col) {
                return true;
            }
        }
        return false;
    }

     /**
     * @brief Retrieves a list of reserved positions on the map.
     *
     * Reserved positions include starting positions for players and nearby grass
     * squares, ensuring these areas are not blocked by walls.
     *
     * @param rows The total number of rows in the map.
     * @param cols The total number of columns in the map.
     * @return A vector of reserved positions as row-column pairs.
     */
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
