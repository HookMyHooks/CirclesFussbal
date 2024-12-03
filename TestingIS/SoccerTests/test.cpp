#include "Game.h"
#include "pch.h"
#include "IGameListener.h"
#include "EPlayer.h"
#include "IGame.h"

using ::testing::_;
using ::testing::Exactly;

// Mock class for IGameListener
class MockGameListener : public IGameListener {
public:
    MOCK_METHOD(void, OnWin, (), (override));
};

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = IGame::Produce();
    }

    std::shared_ptr<IGame> game;
};

// Test for initial state
TEST_F(GameTest, InitialState) {
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
}

// Test for player switching
TEST_F(GameTest, SwitchPlayers) {
    game->SwitchPlayers();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER2);

    game->SwitchPlayers();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
}

// Test for game reset
TEST_F(GameTest, ResetGame) {
    game->SwitchPlayers();
    game->UpdateScore(EPlayer::PLAYER1);
    game->UpdateScore(EPlayer::PLAYER2);

    game->ResetGame();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
}

// Test for score updating
TEST_F(GameTest, UpdateScore) {
    game->UpdateScore(EPlayer::PLAYER1);
    game->UpdateScore(EPlayer::PLAYER2);
    game->UpdateScore(EPlayer::PLAYER2);

    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
}
