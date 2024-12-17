#include "GameUI.h"
#include <iostream>
#include "InputHandler.h"
#include "SpriteHandler.h"

void GameUI::initVariables(EDifficulty difficulty)
{
	this->game = new Game(difficulty);
	game->addGameListener(this);
	if (!this->gameOverTexture.loadFromFile(Constants::GameOverPath)) {
		std::cerr << "Failed to load Game Over image!" << std::endl;
	}
	this->gameOverSprite.setTexture(this->gameOverTexture);

	float scaleX = 800.0f / this->gameOverTexture.getSize().x;
	float scaleY = 800.0f / this->gameOverTexture.getSize().y;
	this->gameOverSprite.setScale(scaleX, scaleY);
	this->gameOverSprite.setPosition(0, 0);

}

void GameUI::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Bomberman");
}

void GameUI::initTimer()
{
	if (!font.loadFromFile(Constants::fontArialPath))
	{
		std::cerr << "Error: Could not load font!" << std::endl;
		return;
	}
	timer.setFont(font);
	timer.setCharacterSize(24);
	timer.setFillColor(sf::Color::Red);
	timer.setPosition(10, 10);
}

GameUI::GameUI(EDifficulty difficulty)
{
	this->initVariables(difficulty);
	this->initWindow();
	this->initTimer();
}

GameUI::~GameUI()
{
	delete this->window;
	delete this->game;
}

void GameUI::startNewGame(EDifficulty difficulty)
{
	delete this->game;
	this->game = new Game(difficulty);
	game->addGameListener(this);
	game->notifyAllListeners();
}

void GameUI::Update(float elapsedTime)
{
	this->game->HandleExplosion(elapsedTime);
	this->game->UpdateTimer(elapsedTime);
	this->game->HandleActiveFire(elapsedTime);
	this->pollEvents();
}

void GameUI::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->game->isOver()) {
				if (this->ev.key.code == sf::Keyboard::R) 
				{
					std::pair<int,int>mapDimensions = this->game->getMap()->GetMapDimensions();
					if (mapDimensions.first == 10)
					{
						startNewGame(EDifficulty::Easy);
					}
					else if (mapDimensions.first == 15)
					{
						startNewGame(EDifficulty::Medium);
					}
					else if (mapDimensions.first == 18);
					{
						startNewGame(EDifficulty::Hard);
					}
				}
			}
			else {
				InputHandler::HandleKeyPress(this->ev, this->game, this->window);
			}
			break;
		}
	}
}

void GameUI::render()
{
	this->window->clear();
	if (!this->game->isOver()) {
		int minutes = static_cast<int>(game->GetGameTimer()) / 60;
		int seconds = static_cast<int>(game->GetGameTimer()) % 60;
		timer.setString("Time:" + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
		
		float gameTimer = this->game->GetGameTimer();
		const auto& board = this->game->getMap()->getBoard();
		for (const auto& row : board) {
			for (const auto* square : row) {
				renderObjectsOnSquare(square);
			}
		}
		this->window->draw(timer);
	}
	else {
		this->window->draw(this->gameOverSprite);
	}

	this->window->display();
}

template <typename T>
void renderObject(const T* object, SpriteHandler& spriteManager, const std::pair<int, int>& position)
{
	if (object)
	{
		std::string imagePath = object->GetImagePath();
		spriteManager.DrawEntity(imagePath, position);
	}
}


void GameUI::renderObjectsOnSquare(const ISquare* square)
{
	SpriteHandler spriteManager(this->window, 57.0f);

	std::pair<int, int> squarePosition = square->GetPosition();

	renderObject(square, spriteManager, squarePosition);
	renderObject(square->GetPlayer(), spriteManager, squarePosition);
	renderObject(square->GetBomb(), spriteManager, squarePosition);
	renderObject(square->GetFire(), spriteManager, squarePosition);
}

const bool GameUI::running() const
{
	return this->window->isOpen();
}

void GameUI::OnKeyPressed()
{
	this->render();
}
