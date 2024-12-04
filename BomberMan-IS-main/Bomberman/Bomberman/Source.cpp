#include "GameUI.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    GameUI* game = new GameUI();

    sf::Clock clock;
    float elapsedTime = 0.0f;
    game->render();
    while (game->running())
    {
        elapsedTime = clock.restart().asSeconds();
        game->Update(elapsedTime);
    }

    delete game;
    return 0;
}
