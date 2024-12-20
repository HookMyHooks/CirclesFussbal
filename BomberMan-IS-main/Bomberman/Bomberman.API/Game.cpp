#include "Game.h"
#include "EasyMapStrategy.h"
#include "MediumMapStrategy.h"
#include "HardMapStrategy.h"

/**
 * @brief Constructs the Game object and initializes players, map, and game state.
 *
 * Selects a map strategy based on the provided difficulty level, initializes players,
 * and creates the game map. The game timer is set to 100 seconds by default.
 *
 * @param mapDifficulty The difficulty level for the map (Easy, Medium, Hard).
 */
Game::Game(EDifficulty mapDifficulty) : gameIsOver(false), gameTimer(300.0f)
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

/**
 * @brief Destructor for the Game class.
 *
 * Cleans up dynamically allocated memory for the map, players, active bombs, and active fire.
 */
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

/**
 * @brief Adds a game listener to the game.
 *
 * @param listener A pointer to an object implementing IGameListener.
 * @return True if the listener was successfully added.
 */
bool Game::addGameListener(IGameListener* listener)
{
    listeners.push_back(listener);
    return true;
}

/**
 * @brief Removes a game listener from the game.
 *
 * @param listener A pointer to an object implementing IGameListener.
 * @return True if the listener was successfully removed.
 */
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

/**
 * @brief Notifies all listeners that a game event has occurred.
 */
void Game::notifyAllListeners()
{
    for (auto* listener : listeners) {
        listener->OnKeyPressed();
    }
}

/**
 * @brief Retrieves the game map.
 *
 * @return A pointer to the current map object.
 */
IMap* Game::getMap()
{
    return map;
}

/**
 * @brief Checks if the game is over.
 *
 * @return True if the game is over, otherwise false.
 */
bool Game::isOver()
{
    return this->gameIsOver;
}

/**
 * @brief Retrieves player 1.
 *
 * @return A pointer to the first player object.
 */
IPlayer* Game::GetPlayer1()
{
    return player1;
}

/**
 * @brief Retrieves player 2.
 *
 * @return A pointer to the second player object.
 */
IPlayer* Game::GetPlayer2()
{
    return player2;
}

/**
 * @brief Retrieves the remaining game timer.
 *
 * @return The remaining game time as a float.
 */
float Game::GetGameTimer()
{
    return gameTimer;
}

/**
 * @brief Sets the game as over and notifies all listeners.
 */
void Game::SetGameOver()
{
    this->gameIsOver = true;
    notifyAllListeners();
}

/**
 * @brief Moves a player in a specified direction.
 *
 * Validates the move and updates the player's position on the map. If the player encounters fire,
 * the game ends.
 *
 * @param player A pointer to the player to be moved.
 * @param movementDir The direction in which the player moves.
 */
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
            return;
        }
        player->SetLastMoveTime(std::chrono::steady_clock::now());
        targetSquare->SetPlayer(player);

        ISquare* currentSquare = this->map->GetSquare(oldPosition.first, oldPosition.second);
        currentSquare->RemovePlayer();
        notifyAllListeners();
    }
}

/**
 * @brief Places a bomb at the player's current position.
 *
 * @param player A pointer to the player placing the bomb.
 */
void Game::PlaceBomb(IPlayer* player)
{
    std::pair<int, int> playerPosition = player->GetPosition();
    if (!this->map->HasBombOnSquare(playerPosition) && !player->HasPlacedBomb())
    {
        this->map->PlaceBomb(playerPosition.first, playerPosition.second);
        player->StatePlaceBomb();
        activeBombs.push_back(std::make_tuple(playerPosition.first, playerPosition.second, player));

        notifyAllListeners();
    }
}

/**
 * @brief Handles bomb explosions, updating fire and the game map.
 *
 * @param elapsedTime The time elapsed since the last update.
 */
void Game::HandleExplosion(float elapsedTime)
{
    bool stateActiveBombs = false;
    for (auto bomb = activeBombs.begin(); bomb != activeBombs.end();)
    {
        ISquare* square = map->GetSquare(std::get<0>((*bomb)), std::get<1>((*bomb)));
        if (square && square->GetBomb())
        {
            square->GetBomb()->UpdateTimer(elapsedTime);
            if (square->HasBombExploded())
            {
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
                bomb++;
        }
    }
    if (stateActiveBombs)
        notifyAllListeners();
}

/**
 * @brief Updates the game timer.
 *
 * @param elapsedTime The time elapsed since the last update.
 */
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

void Game::UpdateMap(std::pair<int, int> position, int rangeBomb)
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
            int targetRow = row + (distance + 1) * direction.first;
            int targetCol = col + (distance + 1) * direction.second;
            if (targetRow < 0 || targetCol < 0 || targetRow >= map->GetMapDimensions().first || targetCol >= map->GetMapDimensions().second) {
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
