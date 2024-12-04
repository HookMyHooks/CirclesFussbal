#include "InputHandler.h"

const std::unordered_map<sf::Keyboard::Key, EPlayerMovementType> InputHandler::player1Keys = {
    {sf::Keyboard::W, EPlayerMovementType::Up},
    {sf::Keyboard::A, EPlayerMovementType::Left},
    {sf::Keyboard::S, EPlayerMovementType::Down},
    {sf::Keyboard::D, EPlayerMovementType::Right}
};

const std::unordered_map<sf::Keyboard::Key, EPlayerMovementType> InputHandler::player2Keys = {
    {sf::Keyboard::Up, EPlayerMovementType::Up},
    {sf::Keyboard::Left, EPlayerMovementType::Left},
    {sf::Keyboard::Down, EPlayerMovementType::Down},
    {sf::Keyboard::Right, EPlayerMovementType::Right}
};

void InputHandler::HandleKeyPress(sf::Event& event, IGame* game, sf::RenderWindow* window)
{
    if (event.key.code == sf::Keyboard::Escape) {
        window->close();
    }
    else {
        HandlePlayerMovement(event, game);
        HandleBombPlacement(event, game);
    }
}

void InputHandler::HandlePlayerMovement(sf::Event& event, IGame* game)
{
    auto movePlayer1 = player1Keys.find(event.key.code);
    auto movePlayer2 = player2Keys.find(event.key.code);

    if (movePlayer1 != player1Keys.end())
    {
        game->MovePlayer(game->GetPlayer1(), (*movePlayer1).second);
    }
    else if (movePlayer2 != player2Keys.end())
    {
        game->MovePlayer(game->GetPlayer2(), (*movePlayer2).second);
    }
}

void InputHandler::HandleBombPlacement(sf::Event& event, IGame* game)
{
    if (event.key.code == sf::Keyboard::N) {
        game->PlaceBomb(game->GetPlayer2());
    }
    else if (event.key.code == sf::Keyboard::F) {
        game->PlaceBomb(game->GetPlayer1());
    }
}
