#include "EasyMapStrategy.h"

/**
 * @brief Generates a 10x10 game map with walls, grass, and player positions.
 *
 * This method creates a map grid for a game where the perimeter is unbreakable walls,
 * and the interior contains random breakable walls or grass tiles. Players are positioned
 * at designated starting points.
 *
 * @param player1 A pointer to the first player, to be placed on the board.
 * @param player2 A pointer to the second player, to be placed on the board.
 *
 * @return A 2D vector of ISquare pointers representing the generated game map.
 */
std::vector<std::vector<ISquare*>> EasyMapStrategy::GenerateMap(IPlayer* player1, IPlayer* player2) {
    rows = 10;
    collumns = 10;
    std::vector<std::vector<ISquare*>> board;

    // Get reserved positions dynamically
    std::vector<std::pair<int, int>> reservedPositions = MapGenerationUtils::GetReservedPositions(rows, collumns);

    for (int line = 0; line < rows; line++) {
        std::vector<ISquare*> row;
        MapGenerationUtils::GenerateRow(row, line, collumns, rows, reservedPositions);
        board.push_back(row);
    }

    // Place players
    board[1][1]->SetPlayer(player1);
    board[rows - 2][collumns - 2]->SetPlayer(player2);

    return board;
}