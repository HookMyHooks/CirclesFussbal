#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game.h"

using ::testing::Exactly;

// Mock class for IGameListener
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

// Test for listeners
TEST_F(GameTest, NotifyListenersOnWin) {
    MockGameListener listener1, listener2;
    game->AddListener(&listener1);
    game->AddListener(&listener2);

    EXPECT_CALL(listener1, OnWin()).Times(Exactly(1));
    EXPECT_CALL(listener2, OnWin()).Times(Exactly(1));

    game->NotifyListenersOnWin();
}

// Test for adding and removing listeners
TEST_F(GameTest, AddAndRemoveListeners) {
    MockGameListener listener1, listener2;
    game->AddListener(&listener1);
    game->AddListener(&listener2);

    EXPECT_CALL(listener1, OnWin()).Times(Exactly(1));
    EXPECT_CALL(listener2, OnWin()).Times(Exactly(1));
    game->NotifyListenersOnWin();

    game->RemoveListener(&listener1);

    EXPECT_CALL(listener1, OnWin()).Times(Exactly(0));
    EXPECT_CALL(listener2, OnWin()).Times(Exactly(1));
    game->NotifyListenersOnWin();
}

// Test for listener clearing upon reset
TEST_F(GameTest, ResetClearsListeners) {
    MockGameListener listener;
    game->AddListener(&listener);

    EXPECT_CALL(listener, OnWin()).Times(0);

    game->ResetGame();
}

//Test to ensure no crash when notifying listeners on an empty list.
TEST_F(GameTest, NotifyListenersOnEmptyList) {
    EXPECT_NO_THROW(game->NotifyListenersOnWin());
}

// Test edge case for listener removal (removing non-existent listener).
TEST_F(GameTest, RemoveNonExistentListener) {
    MockGameListener listener1, listener2;

    game->AddListener(&listener1);
    game->RemoveListener(&listener2);

    EXPECT_CALL(listener1, OnWin()).Times(1);
    game->NotifyListenersOnWin();
}

// Test to check behavior when scoring with no listeners.
TEST_F(GameTest, ScoreUpdateWithNoListeners) {
    EXPECT_NO_THROW(game->UpdateScore(EPlayer::PLAYER1));
}

// Test edge case for ResetGame when no actions were taken.
TEST_F(GameTest, ResetGameWithoutActions) {
    game->ResetGame();
    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
}