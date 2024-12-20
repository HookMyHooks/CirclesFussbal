#include "MediumMapStrategy.h"

/**
 * @brief Generates a medium-difficulty game map with a mix of unbreakable walls, breakable walls, and grass.
 *
 * The edges of the map are filled with unbreakable walls. The inner area is randomly populated
 * with either grass or breakable walls. Player positions are predefined at specific locations.
 *
 * @param player1 Pointer to the first player, placed at position (1,1).
 * @param player2 Pointer to the second player, placed near the bottom-right at (rows-2, columns-2).
 * @return A 2D vector of ISquare pointers representing the generated game board.
 */
std::vector<std::vector<ISquare*>> MediumMapStrategy::GenerateMap(IPlayer* player1, IPlayer* player2)
{
    rows = 15;
    collumns = 20;
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
