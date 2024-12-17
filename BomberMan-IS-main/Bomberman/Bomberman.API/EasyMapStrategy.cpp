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
std::vector<std::vector<ISquare*>> EasyMapStrategy::GenerateMap(IPlayer* player1, IPlayer* player2)
{
    rows = 10;      ///< Number of rows in the game map.
    collumns = 10;  ///< Number of columns in the game map.
    std::vector<std::vector<ISquare*>> board;

    for (int line = 0; line < rows; line++) {
        std::vector<ISquare*> lineVector;
        for (int col = 0; col < collumns; col++) {
            ISquare* square = nullptr;

            // Create unbreakable walls along the edges of the board
            if (line == 0 || line == rows - 1 || col == 0 || col == collumns - 1) {
                square = new Square(
                    { line, col },
                    nullptr,
                    ESquareType::UnbreakableWall,
                    Constants::WallUnbreakablePNGPath
                );
            }
            else {
                // Randomly assign grass or breakable walls inside the map
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

    // Set player positions on the board
    board[1][1]->SetPlayer(player1);
    board[rows - 2][collumns - 2]->SetPlayer(player2);

    return board;
}
