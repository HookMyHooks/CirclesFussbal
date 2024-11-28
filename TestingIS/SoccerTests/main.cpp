#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game.h"

//using namespace testing;
//
//class MockGameListener : public IGameListener {
//public:
//    MOCK_METHOD(void, OnWin, (), (override));
//};
//
//class GameTest : public ::testing::Test {
//protected:
//    void SetUp() override {
//        game = std::make_shared<Game>();
//    }
//
//    std::shared_ptr<Game> game;
//};
//
//TEST_F(GameTest, InitialState) {
//    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
//    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
//}
//
//TEST_F(GameTest, SwitchPlayers) {
//    game->SwitchPlayers();
//    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER2);
//
//    game->SwitchPlayers();
//    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
//}
//
//TEST_F(GameTest, ResetGame) {
//    game->SwitchPlayers();
//    game->UpdateScore(EPlayer::PLAYER1);
//    game->UpdateScore(EPlayer::PLAYER2);
//
//    game->ResetGame();
//    EXPECT_EQ(game->GetCurrentPlayer(), EPlayer::PLAYER1);
//    EXPECT_EQ(game->GetPlayerObjects().size(), 0);
//}
//
//TEST_F(GameTest, UpdateScore) {
//    game->UpdateScore(EPlayer::PLAYER1);
//    game->UpdateScore(EPlayer::PLAYER2);
//
//    EXPECT_EQ(game->GetScore(EPlayer::PLAYER1), 0);
//    EXPECT_EQ(game->GetScore(EPlayer::PLAYER2), 1);
//}
//
//TEST_F(GameTest, NotifyListenersOnWin) {
//    MockGameListener mockListener;
//    EXPECT_CALL(mockListener, OnWin()).Times(1);
//
//    game->AddListener(&mockListener);
//    game->NotifyListenersOnWin();
//}
//
//TEST_F(GameTest, AddAndRemoveListeners) {
//    MockGameListener mockListener1, mockListener2;
//
//    game->AddListener(&mockListener1);
//    game->AddListener(&mockListener2);
//
//    EXPECT_CALL(mockListener1, OnWin()).Times(1);
//    EXPECT_CALL(mockListener2, OnWin()).Times(1);
//
//    game->NotifyListenersOnWin();
//
//    game->RemoveListener(&mockListener1);
//    EXPECT_CALL(mockListener2, OnWin()).Times(1);
//
//    game->NotifyListenersOnWin();
//}

