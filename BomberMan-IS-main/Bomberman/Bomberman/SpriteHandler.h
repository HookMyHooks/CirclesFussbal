#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>

class SpriteHandler {
public:
    SpriteHandler(sf::RenderWindow* window, float gridCellSize);
    ~SpriteHandler() = default;
    sf::Sprite GenerateSprite(const std::string& imagePath);
    void DrawEntity(const std::string& entityImagePath, const std::pair<int, int>& position);

private:
    sf::RenderWindow* window;
    float gridCellSize;
    std::map<std::string, sf::Texture> textureCache;
    sf::Texture& LoadTexture(const std::string& filePath);
};
