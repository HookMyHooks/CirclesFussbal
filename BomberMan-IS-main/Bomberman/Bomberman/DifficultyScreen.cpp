// DifficultyScreen.cpp
#include "DifficultyScreen.h"
#include <iostream>

DifficultyScreen::DifficultyScreen()
{
    initWindow();
    initButtons();
}

DifficultyScreen::~DifficultyScreen()
{
    delete window;
}

void DifficultyScreen::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(600, 400), "Select Difficulty");
}

void DifficultyScreen::initButtons()
{
    if (!font.loadFromFile("../Bomberman.API/Assets/arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        exit(EXIT_FAILURE); // Exit the program if font fails to load
    }


    easyButton.setFont(font);
    easyButton.setString("Easy");
    easyButton.setCharacterSize(60); // Increased font size
    easyButton.setFillColor(sf::Color::Green);
    easyButton.setPosition(200, 100); // Adjusted position

    mediumButton.setFont(font);
    mediumButton.setString("Medium");
    mediumButton.setCharacterSize(60);
    mediumButton.setFillColor(sf::Color::Yellow);
    mediumButton.setPosition(200, 200); // Adjusted position

    hardButton.setFont(font);
    hardButton.setString("Hard");
    hardButton.setCharacterSize(60);
    hardButton.setFillColor(sf::Color::Red);
    hardButton.setPosition(200, 300); // Adjusted position

}

EDifficulty DifficultyScreen::show()
{
    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                this->window->close();
                return EDifficulty::Easy; // Default return if window is closed
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

                if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    this->window->close();
                    return EDifficulty::Easy;
                }
                else if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    this->window->close();
                    return EDifficulty::Medium;
                }
                else if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    this->window->close();
                    return EDifficulty::Hard;
                }
            }
        }

        this->window->clear();
        this->window->draw(easyButton);
        this->window->draw(mediumButton);
        this->window->draw(hardButton);
        this->window->display();
    }

    return EDifficulty::Easy; // Default return
}
