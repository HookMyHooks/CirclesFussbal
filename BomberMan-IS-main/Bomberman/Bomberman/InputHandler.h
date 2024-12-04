#pragma once
#include <SFML/Graphics.hpp>
#include <Game.h>
#include <unordered_map>

class InputHandler {
public:
    static void HandleKeyPress(sf::Event& event, IGame* game, sf::RenderWindow* window);
private:
    static void HandlePlayerMovement(sf::Event& event, IGame* game);
    static void HandleBombPlacement(sf::Event& event, IGame* game);
    static const std::unordered_map<sf::Keyboard::Key, EPlayerMovementType> player1Keys;
    static const std::unordered_map<sf::Keyboard::Key, EPlayerMovementType> player2Keys; 
};


