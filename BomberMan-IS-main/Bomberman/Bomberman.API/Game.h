#pragma once

#include "IGame.h"
#include "IMap.h"
#include "Player.h"
#include "IGameListener.h"
#include "EDifficulty.h"
#include <vector>

class Game : public IGame {
private:
    IMap* map;
    IPlayer* player1;
    IPlayer* player2;
    bool gameIsOver;
    float gameTimer;
    std::vector<std::tuple<int,int,IPlayer*>> activeBombs;
    std::vector<IFire*> activeFire;
    std::vector<IGameListener*> listeners;

public:
    Game(EDifficulty mapDifficulty);
    ~Game();

    IMap* getMap() override;
    bool isOver() override;
    void SetGameOver() override;
    void MovePlayer(IPlayer* player, EPlayerMovementType movementDir) override;
    IPlayer* GetPlayer1() override;
    IPlayer* GetPlayer2() override;
    float GetGameTimer() override;
    
    void PlaceBomb(IPlayer* player) override;
    void HandleExplosion(float elapsedTime) override;
    void HandleActiveFire(const float& elapsedTime) override;
    void UpdateMap(std::pair<int,int> position,int rangeBomb);
    void UpdateTimer(float elapsedTime) override;

    bool addGameListener(IGameListener* listener) override;
    bool removeGameListener(IGameListener* listener) override;
    void notifyAllListeners() override;
};
