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
std::vector<std::vector<ISquare*>> HardMapStrategy::GenerateMap(IPlayer* player1, IPlayer* player2)
{
    rows = 15;       ///< The number of rows in the map.
    collumns = 20;   ///< The number of columns in the map.
    std::vector<std::vector<ISquare*>> board;

    // Generate the grid row by row
    for (int line = 0; line < rows; line++) {
        std::vector<ISquare*> lineVector;
        for (int col = 0; col < collumns; col++) {
            ISquare* square = nullptr;

            // Create unbreakable walls at the borders
            if (line == 0 || line == rows - 1 || col == 0 || col == collumns - 1) {
                square = new Square({ line, col }, nullptr, ESquareType::UnbreakableWall, Constants::WallUnbreakablePNGPath);
            }
            else {
                // Randomly place grass or breakable walls in inner cells
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> dis(0, 1);

                if (dis(gen) == 0) {
                    square = new Square({ line, col }, nullptr, ESquareType::Grass, Constants::GrassPNGPath);
                }
                else {
                    square = new Square({ line, col }, nullptr, ESquareType::Wall, Constants::WallBreakablePNGPath);
                }
            }

            lineVector.push_back(square);
        }
        board.push_back(lineVector);
    }

    // Place players at their starting positions
    board[1][1]->SetPlayer(player1);                        ///< Player 1 starts at position (1,1).
    board[rows - 2][collumns - 2]->SetPlayer(player2);      ///< Player 2 starts at position (rows-2, columns-2).

    return board;
}
