#include "SpriteHandler.h"


SpriteHandler::SpriteHandler(sf::RenderWindow* window, float gridCellSize)
    : window(window), gridCellSize(gridCellSize) {
}

sf::Texture& SpriteHandler::LoadTexture(const std::string& filePath) {
    if (textureCache.find(filePath) == textureCache.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(filePath)) {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            throw std::runtime_error("Texture loading failed");
        }
        textureCache[filePath] = std::move(texture);
    }
    return textureCache[filePath];
}

sf::Sprite SpriteHandler::GenerateSprite(const std::string& imagePath) {
    sf::Texture& texture = LoadTexture(imagePath);
    sf::Sprite sprite(texture);

    float scaleX = gridCellSize / texture.getSize().x;
    float scaleY = gridCellSize / texture.getSize().y;
    sprite.setScale(scaleX, scaleY);

    return sprite;
}

void SpriteHandler::DrawEntity(const std::string& entityImagePath, const std::pair<int, int>& position) {
    sf::Sprite sprite = GenerateSprite(entityImagePath);

    sprite.setPosition(static_cast<float>(position.second * gridCellSize),
        static_cast<float>(position.first * gridCellSize));

    window->draw(sprite);
}
