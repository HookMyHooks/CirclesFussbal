#include "Player.h"

Player::Player(EPlayerType playerType, int startX, int startY)
    : type(playerType), position(startX, startY), alive(true), placeBomb(false), activePowerup(false)
{
    imagePath = type == EPlayerType::One ? Constants::Player1PNGPath : Constants::Player2PNGPath;
    if (!Constants::isValidPath(imagePath)) {
        std::cerr << "Image does not exist: " << imagePath << std::endl;
    }
    lastMoveTime = std::chrono::steady_clock::now();
    moveDelay = 0.4f;
}

std::pair<int, int> Player::GetPosition() const {
    return position;
}

bool Player::HasPlacedBomb() const {
    return placeBomb;
}

std::string Player::GetImagePath() const {
    return imagePath;
}

void Player::SetPosition(int x, int y) {
    position = std::make_pair(x, y);
}

void Player::StatePlaceBomb() {
    placeBomb = !placeBomb;
}

void Player::SetImagePath(const std::string& path) {
    imagePath = path;
}

void Player::SetLastMoveTime(const std::chrono::steady_clock::time_point& newTime)
{
    lastMoveTime = newTime;
}

bool Player::CanMove()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime).count();
    return elapsed >= (moveDelay * 1000);
}
