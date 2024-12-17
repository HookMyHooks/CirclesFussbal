#include "Game.h"
#include "EasyMapStrategy.h"
#include "MediumMapStrategy.h"
#include "HardMapStrategy.h"

Game::Game(EDifficulty mapDifficulty) : gameIsOver(false), gameTimer(100.0f)
{
    this->player1 = new Player(EPlayerType::One, 1, 1);
    this->player2 = new Player(EPlayerType::Two, 12, 12);
    // Select strategy based on the provided difficulty
    IMapStrategy* strategy = nullptr;

    switch (mapDifficulty)
    {
    case EDifficulty::Easy:
        strategy = new EasyMapStrategy();
        break;
    case EDifficulty::Medium:
        strategy = new MediumMapStrategy();
        break;
    case EDifficulty::Hard:
        strategy = new HardMapStrategy();
        break;
    default:
        throw std::invalid_argument("Invalid difficulty level");
    }

    this->map = new Map(player1, player2, strategy);

    // Clean up the strategy after use
    delete strategy;
}

Game::~Game() {
    map->ResetMap();
    delete map;
    delete player1;
    delete player2;
    for (auto fire : activeFire)
    {
        delete fire;
    }
    activeFire.clear();
    activeBombs.clear();
}

bool Game::addGameListener(IGameListener* listener) 
{
    listeners.push_back(listener);
    return true;
}

bool Game::removeGameListener(IGameListener* listener) 
{
    for (auto it = listeners.begin(); it != listeners.end(); ++it)
    {
        if (*it == listener)
        {
            listeners.erase(it);
            return true;
        }
    }

    return false;
}

void Game::notifyAllListeners()
{
    for (auto* listener : listeners) {
        listener->OnKeyPressed();
    }
}

IMap* Game::getMap()
{
    return map;
}

bool Game::isOver()
{
    return this->gameIsOver;
}

IPlayer* Game::GetPlayer1()
{
    return player1;
}

IPlayer* Game::GetPlayer2()
{
    return player2;
}

float Game::GetGameTimer()
{
    return gameTimer;
}

void Game::SetGameOver()
{
    this->gameIsOver = true;
    notifyAllListeners();
}

void Game::MovePlayer(IPlayer* player, EPlayerMovementType movementDir)
{
    if (!player->CanMove())
        return;

    std::pair<int, int> oldPosition = player->GetPosition();
    std::pair<int, int> newPosition = oldPosition;

    switch (movementDir)
    {
    case EPlayerMovementType::Up:
        newPosition.first -= 1;
        break;
    case EPlayerMovementType::Down:
        newPosition.first += 1;
        break;
    case EPlayerMovementType::Left:
        newPosition.second -= 1;
        break;
    case EPlayerMovementType::Right:
        newPosition.second += 1;
        break;
    }

    ISquare* targetSquare = this->map->GetSquare(newPosition.first, newPosition.second);
    if (targetSquare && targetSquare->HasWall() && !targetSquare->HasPlayer())
    {
        if (targetSquare->HasFire())
        {
            this->SetGameOver();
            notifyAllListeners();
            return;
        }
        player->SetLastMoveTime(std::chrono::steady_clock::now());
        targetSquare->SetPlayer(player);

        ISquare* currentSquare = this->map->GetSquare(oldPosition.first, oldPosition.second);
        currentSquare->RemovePlayer();
        notifyAllListeners();
    }

}

void Game::PlaceBomb(IPlayer* player)
{
    std::pair<int, int> playerPosition = player->GetPosition();
    if (!this->map->HasBombOnSquare(playerPosition) && !player->HasPlacedBomb())
    {
        this->map->PlaceBomb(playerPosition.first, playerPosition.second);
        player->StatePlaceBomb();
        activeBombs.push_back(std::make_tuple(playerPosition.first, playerPosition.second,player));

        notifyAllListeners();
    }
}

void Game::HandleExplosion(float elapsedTime)
{
    bool stateActiveBombs = false;
    for (auto bomb=activeBombs.begin(); bomb!=activeBombs.end();)
    {
        ISquare* square = map->GetSquare(std::get<0>((*bomb)), std::get<1>((*bomb)));
        if (square && square->GetBomb())
        {
            square->GetBomb()->UpdateTimer(elapsedTime);
            if (square->HasBombExploded())
            {
                if (square->HasPlayer())
                {
                    this->SetGameOver();
                    notifyAllListeners();
                    return;
                }
                int rangeBomb = square->GetBomb()->GetRange();
                IFire* fire = new Fire(square->GetPosition(), 2);
                square->SetFire(fire);
                activeFire.push_back(fire);
                square->ClearBomb();
                std::get<2>((*bomb))->StatePlaceBomb();
                bomb = activeBombs.erase(bomb);
                UpdateMap(square->GetPosition(), rangeBomb);

                stateActiveBombs = true;
            }
            else
            {
                bomb++;
            }

        }
    }
    if (stateActiveBombs)
        notifyAllListeners();


}

void Game::HandleActiveFire(const float& elapsedTime)
{
    bool activeFireState = false;

    for (auto fire = activeFire.begin(); fire != activeFire.end();)
    {
        if ((*fire)->HasExpired(elapsedTime))
        {   
            std::pair<int, int> positionFire = (*fire)->GetPosition();
            ISquare* square = map->GetSquare(positionFire.first, positionFire.second);
            square->ClearFire();
            fire = activeFire.erase(fire);
            activeFireState = true;
        }
        else
            fire++;
    }
    if (activeFireState)
        notifyAllListeners();

}

void Game::UpdateMap(std::pair<int,int> position,int rangeBomb)
{
    std::vector<std::pair<int, int>> directions = {
          { 0, 1}, 
          { 0, -1}, 
          { 1, 0}, 
          {-1, 0}  
    };
    int row = position.first;
    int col = position.second;
    for (auto& direction : directions)
    {
        for (int distance = 0; distance < rangeBomb; distance++)
        {
            int targetRow = row + (distance+1) * direction.first;
            int targetCol = col + (distance + 1) * direction.second;
            if (targetRow < 0 || targetCol < 0 || targetRow >= map->GetMapDimensions().first || targetCol >= map->GetMapDimensions().second){
                break; 
            }
            ISquare* targetSquare = map->GetSquare(targetRow, targetCol);
            if (targetSquare->GetPlayer())
            {
                this->SetGameOver();
                return;
            }
            if (targetSquare->GetSquareType() != ESquareType::Grass)
            {
                if (targetSquare->GetSquareType() == ESquareType::Wall)
                {
                    targetSquare->SetSquareType(ESquareType::Grass);
                    targetSquare->SetImagePath(Constants::GrassPNGPath);
                }
                break;

            }
            IFire* fire = new Fire(std::make_pair(targetRow, targetCol), 2);
            targetSquare->SetFire(fire);
            activeFire.push_back(fire);
        }

    }

}

void Game::UpdateTimer(float elapsedTime)
{
    if (gameIsOver) return;

    gameTimer -= elapsedTime;
    if (gameTimer <= 1)
    {
        gameTimer = 0;
        SetGameOver();
    }
    notifyAllListeners();

}
