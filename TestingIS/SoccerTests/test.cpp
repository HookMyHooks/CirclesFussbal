#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game.h"


class MockGameListener : public IGameListener {
public:
    MOCK_METHOD(void, OnWin, (), (override));
};

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_shared<Game>();
    }

    std::shared_ptr<Game> game;
};

TEST_F(GameTest, InitialState) {
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
}

TEST_F(GameTest, SwitchPlayers) {
    game->SwitchPlayers();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER2);

    game->SwitchPlayers();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
}

TEST_F(GameTest, ResetGame) {
    game->SwitchPlayers();
    game->UpdateScore(EPlayer::PLAYER1);
    game->UpdateScore(EPlayer::PLAYER2);

    game->ResetGame();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
}




