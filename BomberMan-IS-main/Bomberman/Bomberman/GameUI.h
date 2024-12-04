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
	
	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;
	sf::Text timer;
	sf::Font font;

	void initVariables();
	void initWindow();
	void initTimer();
	void renderObjectsOnSquare(const ISquare* square);

public:
	GameUI();
	virtual ~GameUI();


	void startNewGame();
	void Update(float elapsedTime);
	void pollEvents();
	void render();
	const bool running() const;
	void OnKeyPressed() override;
};