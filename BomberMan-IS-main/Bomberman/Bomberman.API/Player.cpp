#include "Player.h"

/**
 * @brief Constructs a Player object with initial position and player type.
 *
 * The player image path is determined based on the player type.
 * Validates the image path during initialization and sets the initial move delay.
 *
 * @param playerType The type of player (EPlayerType::One or EPlayerType::Two).
 * @param startX The starting X-coordinate for the player.
 * @param startY The starting Y-coordinate for the player.
 */
Player::Player(EPlayerType playerType, int startX, int startY)
    : type(playerType), position(startX, startY), alive(true), placeBomb(false), activePowerup(false)
{
    // Set the player's image path based on type
    imagePath = type == EPlayerType::One ? Constants::Player1PNGPath : Constants::Player2PNGPath;

    // Validate the image path
    if (!Constants::isValidPath(imagePath)) {
        std::cerr << "Image does not exist: " << imagePath << std::endl;
    }

    lastMoveTime = std::chrono::steady_clock::now();
    moveDelay = 0.4f; ///< Move delay in seconds
}

/**
 * @brief Retrieves the player's current position.
 *
 * @return A pair representing the X and Y coordinates of the player.
 */
std::pair<int, int> Player::GetPosition() const {
    return position;
}

/**
 * @brief Checks if the player has recently placed a bomb.
 *
 * @return True if the player has placed a bomb, false otherwise.
 */
bool Player::HasPlacedBomb() const {
    return placeBomb;
}

/**
 * @brief Retrieves the file path for the player's image.
 *
 * @return A string containing the player's image path.
 */
std::string Player::GetImagePath() const {
    return imagePath;
}

/**
 * @brief Sets the player's position on the map.
 *
 * @param x The new X-coordinate for the player.
 * @param y The new Y-coordinate for the player.
 */
void Player::SetPosition(int x, int y) {
    position = std::make_pair(x, y);
}

/**
 * @brief Toggles the player's bomb placement state.
 *
 * If the player has not placed a bomb, this function sets the state to true.
 * If already placed, it toggles it back to false.
 */
void Player::StatePlaceBomb() {
    placeBomb = !placeBomb;
}

/**
 * @brief Updates the player's image path.
 *
 * @param path A string representing the new image path.
 */
void Player::SetImagePath(const std::string& path) {
    imagePath = path;
}

/**
 * @brief Updates the timestamp of the player's last move.
 *
 * @param newTime The new move time represented as a steady_clock::time_point.
 */
void Player::SetLastMoveTime(const std::chrono::steady_clock::time_point& newTime)
{
    lastMoveTime = newTime;
}

/**
 * @brief Determines if the player is allowed to move based on the move delay.
 *
 * This function checks the time elapsed since the player's last move and compares
 * it against the move delay threshold.
 *
 * @return True if the player can move, false otherwise.
 */
bool Player::CanMove()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime).count();
    return elapsed >= (moveDelay * 1000);
}
