#include "EasyMapStrategy.h"

std::vector<std::vector<ISquare*>> EasyMapStrategy::GenerateMap(IPlayer* player1, IPlayer* player2)
{
    rows = 10;
    collumns = 10;
    std::vector<std::vector<ISquare*>> board;

    for (int line = 0; line < rows; line++) {
        std::vector<ISquare*> lineVector;
        for (int col = 0; col < collumns; col++) {
            ISquare* square = nullptr;

            if (line == 0 || line == rows - 1 || col == 0 || col == collumns - 1) {
                square = new Square({ line, col }, nullptr, ESquareType::UnbreakableWall, Constants::WallUnbreakablePNGPath);
            }
            else {
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

    board[1][1]->SetPlayer(player1);
    board[rows - 2][collumns - 2]->SetPlayer(player2);

    return board;
}