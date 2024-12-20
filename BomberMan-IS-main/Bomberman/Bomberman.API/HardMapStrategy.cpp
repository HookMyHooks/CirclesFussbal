#include "HardMapStrategy.h"

/**
 * @brief Generates a hard difficulty game map with unbreakable walls, grass, and breakable walls.
 *
 * Creates a 15x20 grid-based map. The outermost boundaries are unbreakable walls, while
 * the inner cells randomly contain either grass or breakable walls. Player 1 and Player 2
 * are positioned at predefined locations on the map.
 *
 * @param player1 A pointer to the first player.
 * @param player2 A pointer to the second player.
 * @return A 2D vector of ISquare pointers representing the game map.
 */
std::vector<std::vector<ISquare*>> HardMapStrategy::GenerateMap(IPlayer* player1, IPlayer* player2) {
    rows = 18;
    collumns = 30;
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