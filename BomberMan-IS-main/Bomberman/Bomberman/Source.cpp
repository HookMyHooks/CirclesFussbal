#include "GameUI.h"
#include "DifficultyScreen.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // Show difficulty screen
    DifficultyScreen difficultyScreen;
    EDifficulty selectedDifficulty = difficultyScreen.show();

    // Start the game with the selected difficulty
    GameUI game(selectedDifficulty);

    sf::Clock clock;
    float elapsedTime = 0.0f;
    game.render();
    while (game.running())
    {
        elapsedTime = clock.restart().asSeconds();
        game.Update(elapsedTime);
    }


    return 0;
}
