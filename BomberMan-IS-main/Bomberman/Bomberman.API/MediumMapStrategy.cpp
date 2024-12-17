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
    rows = 15;      ///< Number of rows in the map
    collumns = 20;  ///< Number of columns in the map
    std::vector<std::vector<ISquare*>> board;

    // Loop through each row
    for (int line = 0; line < rows; line++) {
        std::vector<ISquare*> lineVector;

        // Loop through each column
        for (int col = 0; col < collumns; col++) {
            ISquare* square = nullptr;

            // Place unbreakable walls on the edges of the board
            if (line == 0 || line == rows - 1 || col == 0 || col == collumns - 1) {
                square = new Square(
                    { line, col },
                    nullptr,
                    ESquareType::UnbreakableWall,
                    Constants::WallUnbreakablePNGPath
                );
            }
            else {
                // Randomly generate either grass or breakable walls
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

            lineVector.push_back(square);
        }

        board.push_back(lineVector);
    }

    // Place the players at predefined positions
    board[1][1]->SetPlayer(player1);
    board[rows - 2][collumns - 2]->SetPlayer(player2);

    return board;
}
