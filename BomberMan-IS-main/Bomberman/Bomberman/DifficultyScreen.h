// DifficultyScreen.h
#pragma once
#include <SFML/Graphics.hpp>
#include "EDifficulty.h"

class DifficultyScreen {
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text easyButton;
    sf::Text mediumButton;
    sf::Text hardButton;

public:
    DifficultyScreen();
    ~DifficultyScreen();

    void initWindow();
    void initButtons();
    EDifficulty show();
};