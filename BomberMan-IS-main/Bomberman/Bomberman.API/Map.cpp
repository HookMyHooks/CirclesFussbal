#include "Map.h"
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <iostream>

/**
 * @brief Constructs the Map using a strategy to generate the game board.
 *
 * @param player1 Pointer to the first player.
 * @param player2 Pointer to the second player.
 * @param strategy Pointer to a strategy for map generation.
 */
Map::Map(IPlayer* player1, IPlayer* player2, IMapStrategy* strategy) : strategy(strategy)
{
    board = strategy->GenerateMap(player1, player2);
}

/**
 * @brief Initializes the map with default layout, creating unbreakable walls, grass, and breakable walls.
 *
 * Places unbreakable walls on edges, predefined grass cells, and randomizes between grass and breakable walls elsewhere.
 * Players are placed at specific positions on the board.
 *
 * @param player1 Pointer to the first player.
 * @param player2 Pointer to the second player.
 */
void Map::Initialize(IPlayer* player1, IPlayer* player2)
{
    ResetMap();

    for (int line = 0; line < 16; line++) {
        std::vector<ISquare*> lineVector;

        for (int col = 0; col < 16; col++) {
            ISquare* square = nullptr;

            // Unbreakable wall at the edges
            if (line == 0 || line == 15 || col == 0 || col == 15) {
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::UnbreakableWall,
                    Constants::WallUnbreakablePNGPath
                );
            }
            // Predefined grass areas
            else if ((line == 1 && (col == 1 || col == 2)) ||
                (line == 12 && (col == 12 || col == 11)) ||
                (line == 2 && col == 1) ||
                (line == 11 && col == 12)) {
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::Grass,
                    Constants::GrassPNGPath
                );
            }
            // Randomly assign grass or breakable walls
            else {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> dis(0, 1);

                if (dis(gen) == 0) {
                    square = new Square(
                        std::make_pair(line, col),
                        nullptr,
                        ESquareType::Grass,
                        Constants::GrassPNGPath
                    );
                }
                else {
                    square = new Square(
                        std::make_pair(line, col),
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

    // Place players at predefined positions
    board[1][1]->SetPlayer(player1);
    board[12][12]->SetPlayer(player2);
}

/**
 * @brief Resets the map by clearing and deallocating all squares.
 */
void Map::ResetMap()
{
    for (auto& row : board) {
        for (auto* square : row) {
            delete square;
        }
        row.clear();
    }
    board.clear();
}

/**
 * @brief Gets the dimensions of the map as a pair of (rows, columns).
 *
 * @return A pair representing the dimensions of the map.
 */
std::pair<int, int> Map::GetMapDimensions() const
{
    return std::make_pair(board.size(), board[0].size());
}

/**
 * @brief Retrieves the entire board layout.
 *
 * @return A 2D vector of ISquare pointers representing the game board.
 */
std::vector<std::vector<ISquare*>> Map::getBoard() const
{
    return board;
}

/**
 * @brief Retrieves the square at a specific (x, y) position.
 *
 * @param x The row index.
 * @param y The column index.
 * @return A pointer to the ISquare at the given position.
 */
ISquare* Map::GetSquare(int x, int y) const
{
    return board[x][y];
}

/**
 * @brief Checks if there is a bomb at the specified position.
 *
 * @param position The position to check.
 * @return True if a bomb is present; otherwise, false.
 */
bool Map::HasBombOnSquare(std::pair<int, int> position) const
{
    return this->board[position.first][position.second]->HasBomb();
}

/**
 * @brief Places a bomb at the specified (x, y) position.
 *
 * @param x The row index where the bomb will be placed.
 * @param y The column index where the bomb will be placed.
 */
void Map::PlaceBomb(int x, int y)
{
    IBomb* bomb = new Bomb(std::make_pair(x, y), 2, 3);
    this->board[x][y]->SetBomb(bomb);
}

/**
 * @brief Loads a map layout from a file and initializes the board.
 *
 * The file must contain 14 rows and 14 columns, where each value represents a square type:
 * - 0: UnbreakableWall
 * - 1: Grass
 * - 2: Breakable Wall
 *
 * @param filePath The path to the map file.
 * @param player1 Pointer to the first player.
 * @param player2 Pointer to the second player.
 */
void Map::LoadFromFile(std::string filePath, IPlayer* player1, IPlayer* player2)
{
    ResetMap();

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << filePath << "'" << std::endl;
    }

    int line = 0;
    std::string row;
    while (std::getline(file, row) && line < 14) {
        std::istringstream rowStream(row);
        std::vector<ISquare*> lineVector;
        int col = 0;
        int value;

        while (rowStream >> value && col < 14) {
            ISquare* square = nullptr;

            if (value == 0) {
                square = new Square(std::make_pair(line, col), nullptr, ESquareType::UnbreakableWall, Constants::WallUnbreakablePNGPath);
            }
            else if (value == 1) {
                square = new Square(std::make_pair(line, col), nullptr, ESquareType::Grass, Constants::GrassPNGPath);
            }
            else if (value == 2) {
                square = new Square(std::make_pair(line, col), nullptr, ESquareType::Wall, Constants::WallBreakablePNGPath);
            }
            else {
                std::cerr << "Warning: Invalid value at (" << line << ", " << col << "). Defaulting to Grass." << std::endl;
                square = new Square(std::make_pair(line, col), nullptr, ESquareType::Grass, Constants::GrassPNGPath);
            }

            lineVector.push_back(square);
            ++col;
        }

        if (col != 14) {
            std::cerr << "Error: Row " << line << " does not contain 14 columns!" << std::endl;
        }

        board.push_back(lineVector);
        ++line;
    }

    if (line != 14) {
        std::cerr << "Error: File does not contain 14 rows!" << std::endl;
    }

    file.close();

    // Set players at their starting positions
    board[1][1]->SetPlayer(player1);
    board[12][12]->SetPlayer(player2);
}
