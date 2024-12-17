#include "Map.h"
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <iostream>

Map::Map(IPlayer* player1, IPlayer* player2, IMapStrategy* strategy): strategy(strategy)
{
    board = strategy->GenerateMap(player1, player2);
}

void Map::Initialize(IPlayer* player1, IPlayer* player2)
{
    ResetMap();

    //18
    for (int line = 0; line < 16; line++) {
        std::vector<ISquare*> lineVector;
        //30
        for (int col = 0; col < 16; col++) {
            ISquare* square = nullptr;

            // 1. Edges: Set to UnbreakableWall
            if (line == 0 || line == 15 || col == 0 || col == 15) {
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::UnbreakableWall,
                    Constants::WallUnbreakablePNGPath
                );
            }
            // 2. Grass areas
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
            // 3. Remaining cells: randwom between Grass and Wall
            else
            {
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

    board[1][1]->SetPlayer(player1);
    board[12][12]->SetPlayer(player2);
}


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

std::pair<int, int> Map::GetMapDimensions() const
{
    return std::make_pair(board.size(), board[0].size());
}

std::vector<std::vector<ISquare*>> Map::getBoard() const
{
    return board;
}

ISquare* Map::GetSquare(int x, int y) const
{
    return board[x][y];
}

bool Map::HasBombOnSquare(std::pair<int, int> position) const
{
    return this->board[position.first][position.second]->HasBomb();
}

void Map::PlaceBomb(int x, int y)
{

    IBomb* bomb = new Bomb(std::make_pair(x, y),2,3);
    this->board[x][y]->SetBomb(bomb);

}

void Map::LoadFromFile(std::string filePath, IPlayer* player1, IPlayer* player2)
{
    ResetMap();

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file 'board_layout.txt'" << std::endl;
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
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::UnbreakableWall,
                    Constants::WallUnbreakablePNGPath
                );
            }
            else if (value == 1) {
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::Grass,
                    Constants::GrassPNGPath
                );
            }
            else if (value == 2) {
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::Wall,
                    Constants::WallBreakablePNGPath
                );
            }
            else {
                std::cerr << "Warning: Invalid value at (" << line << ", " << col << "). Defaulting to Grass." << std::endl;
                square = new Square(
                    std::make_pair(line, col),
                    nullptr,
                    ESquareType::Grass,
                    Constants::GrassPNGPath
                );
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

    board[1][1]->SetPlayer(player1);
    board[12][12]->SetPlayer(player2);

}


