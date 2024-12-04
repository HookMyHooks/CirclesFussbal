#include "pch.h"

TEST(GameTest, SpawnTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    EXPECT_EQ(game->GetPlayer1()->GetPosition().first, 1);
    EXPECT_EQ(game->GetPlayer1()->GetPosition().second, 1);

    EXPECT_EQ(game->GetPlayer2()->GetPosition().first, 12);
    EXPECT_EQ(game->GetPlayer2()->GetPosition().second, 12);

    delete game;
}

TEST(GameTest, MovePlayer1) {
    Game* game = new Game(EMapInitialization::FromFile);
    IPlayer* player1 = game->GetPlayer1();

    // Move Up
    game->MovePlayer(player1, EPlayerMovementType::Up);
    EXPECT_EQ(player1->GetPosition().first, 1);
    EXPECT_EQ(player1->GetPosition().second, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // Move Down
    game->MovePlayer(player1, EPlayerMovementType::Down);
    EXPECT_EQ(player1->GetPosition().first, 2);
    EXPECT_EQ(player1->GetPosition().second, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // Move Left
    game->MovePlayer(player1, EPlayerMovementType::Left);
    EXPECT_EQ(player1->GetPosition().first, 2);
    EXPECT_EQ(player1->GetPosition().second, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // Move Right
    game->MovePlayer(player1, EPlayerMovementType::Right);
    EXPECT_EQ(player1->GetPosition().first, 2);
    EXPECT_EQ(player1->GetPosition().second, 2);

    delete game;
}

TEST(GameTest, MovePlayer2) {
    Game* game = new Game(EMapInitialization::FromFile);
    IPlayer* player2 = game->GetPlayer2();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Move Up
    game->MovePlayer(player2, EPlayerMovementType::Up);
    EXPECT_EQ(player2->GetPosition().first, 11);
    EXPECT_EQ(player2->GetPosition().second, 12);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // Move Down
    game->MovePlayer(player2, EPlayerMovementType::Down);
    EXPECT_EQ(player2->GetPosition().first, 12);
    EXPECT_EQ(player2->GetPosition().second, 12);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // Move Left
    game->MovePlayer(player2, EPlayerMovementType::Left);
    EXPECT_EQ(player2->GetPosition().first, 12);
    EXPECT_EQ(player2->GetPosition().second, 11);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // Move Right
    game->MovePlayer(player2, EPlayerMovementType::Right);
    EXPECT_EQ(player2->GetPosition().first, 12);
    EXPECT_EQ(player2->GetPosition().second, 12);

    delete game;
}

TEST(GameTest, GameOver) {
    IGame* game = new Game(EMapInitialization::FromFile);
    EXPECT_FALSE(game->isOver());
    game->SetGameOver();
    EXPECT_TRUE(game->isOver());
    delete game;
}

class MockGameListener : public IGameListener {
public:
    MOCK_METHOD(void, OnKeyPressed, (), (override));
};

TEST(GameTest, AddRemoveGameListener) {
    IGame* game = new Game(EMapInitialization::FromFile);
    MockGameListener listener1, listener2;
    EXPECT_TRUE(game->addGameListener(&listener1));
    EXPECT_TRUE(game->addGameListener(&listener2));
    EXPECT_TRUE(game->removeGameListener(&listener1));
    EXPECT_FALSE(game->removeGameListener(&listener1));
    EXPECT_TRUE(game->removeGameListener(&listener2));
    delete game;
}

TEST(GameTest, ListenerCallTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);
    MockGameListener* listener = new MockGameListener();

    EXPECT_CALL(*listener, OnKeyPressed).Times(1);

    game->addGameListener(listener);
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);   
    
    delete game;
}

TEST(GameTest, MultipleBombsPlacedBySamePlayer)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    game->PlaceBomb(game->GetPlayer1());

    EXPECT_TRUE(game->getMap()->GetSquare(game->GetPlayer1()->GetPosition().first, game->GetPlayer1()->GetPosition().second)->HasBomb());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);

    game->PlaceBomb(game->GetPlayer1());

    EXPECT_FALSE(game->getMap()->GetSquare(game->GetPlayer1()->GetPosition().first, game->GetPlayer1()->GetPosition().second)->HasBomb());

    delete game;
}

TEST(GameTest, ExplosionDestroyTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    EXPECT_EQ(game->getMap()->GetSquare(2, 3)->GetSquareType(), ESquareType::Wall);
    EXPECT_EQ(game->getMap()->GetSquare(3, 2)->GetSquareType(), ESquareType::Wall);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_EQ(game->GetPlayer1()->GetPosition().first, 2);
    EXPECT_EQ(game->GetPlayer1()->GetPosition().second, 2);

    game->PlaceBomb(game->GetPlayer1());

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Up);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Left);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->HandleExplosion(3);

    EXPECT_EQ(game->getMap()->GetSquare(2, 3)->GetSquareType(), ESquareType::Grass);
    EXPECT_EQ(game->getMap()->GetSquare(3, 2)->GetSquareType(), ESquareType::Grass);

    EXPECT_FALSE(game->isOver());

    delete game;
}

TEST(GameTest, ExplosionPlayerInPlaceTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);
    game->PlaceBomb(game->GetPlayer1());
    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;
}

TEST(GameTest, ExplosionPLayerNextToBomb)
{
    IGame* game = new Game(EMapInitialization::FromFile);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->PlaceBomb(game->GetPlayer1());

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;

    game = new Game(EMapInitialization::FromFile);

    game->PlaceBomb(game->GetPlayer1());

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());
    
    delete game;

    game = new Game(EMapInitialization::FromFile);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);
    game->PlaceBomb(game->GetPlayer1());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Left);
    
    game->HandleExplosion(3);
    
    EXPECT_TRUE(game->isOver());

    delete game;
    
    game = new Game(EMapInitialization::FromFile);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);
    game->PlaceBomb(game->GetPlayer1());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Up);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;
}

TEST(GameTest, ExplosionPlayerTwoApartTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    game->PlaceBomb(game->GetPlayer1());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;

    game = new Game(EMapInitialization::FromFile);

    game->PlaceBomb(game->GetPlayer1());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;

    game = new Game(EMapInitialization::FromFile);

    game->PlaceBomb(game->GetPlayer2());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer2(), EPlayerMovementType::Up);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer2(), EPlayerMovementType::Up);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;

    game = new Game(EMapInitialization::FromFile);

    game->PlaceBomb(game->GetPlayer2());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer2(), EPlayerMovementType::Left);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer2(), EPlayerMovementType::Left);

    game->HandleExplosion(3);

    EXPECT_TRUE(game->isOver());

    delete game;
}

TEST(GameTest, FireTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->PlaceBomb(game->GetPlayer1());

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Up);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Left);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->HandleExplosion(3);

    EXPECT_TRUE(game->getMap()->GetSquare(2, 2)->HasFire());
    EXPECT_TRUE(game->getMap()->GetSquare(2, 1)->HasFire());
    EXPECT_TRUE(game->getMap()->GetSquare(1, 2)->HasFire());

    delete game;
}

TEST(GameTest, FirePlayerTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->PlaceBomb(game->GetPlayer1());

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Up);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Left);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->HandleExplosion(3);

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);

    EXPECT_TRUE(game->isOver());

    delete game;
}

TEST(GameTest, FireDisappearTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Down);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Right);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->PlaceBomb(game->GetPlayer1());

    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Up);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game->MovePlayer(game->GetPlayer1(), EPlayerMovementType::Left);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    game->HandleExplosion(3);

    EXPECT_TRUE(game->getMap()->GetSquare(2, 2)->HasFire());
    EXPECT_TRUE(game->getMap()->GetSquare(2, 1)->HasFire());
    EXPECT_TRUE(game->getMap()->GetSquare(1, 2)->HasFire());

    game->HandleActiveFire(2);

    EXPECT_FALSE(game->getMap()->GetSquare(2, 2)->HasFire());
    EXPECT_FALSE(game->getMap()->GetSquare(2, 1)->HasFire());
    EXPECT_FALSE(game->getMap()->GetSquare(1, 2)->HasFire());

    delete game;
}

TEST(GameTest, GameOverTimerTest)
{
    IGame* game = new Game(EMapInitialization::FromFile);

    game->UpdateTimer(100);

    EXPECT_TRUE(game->isOver());

    delete game;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

