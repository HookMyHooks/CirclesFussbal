#pragma once
#define NOMINMAX
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "Game.h"



class GameUI : public IGameListener
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	IGame* game;
	std::map<std::string, sf::Texture> textureCache;
	EDifficulty mapDifficulty;
	
	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;
	sf::Text timer;
	sf::Font font;

	void initVariables(EDifficulty difficulty);
	void initWindow();
	void initTimer();
	void renderObjectsOnSquare(const ISquare* square);

public:
	GameUI(EDifficulty difficulty);
	virtual ~GameUI();


	void startNewGame(EDifficulty difficulty);
	void Update(float elapsedTime);
	void pollEvents();
	void render();
	const bool running() const;
	void OnKeyPressed() override;
};