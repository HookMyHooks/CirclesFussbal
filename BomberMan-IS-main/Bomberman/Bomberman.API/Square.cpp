#include "Square.h"
#include <iostream>

/**
 * @brief Constructs a Square object with position, player, square type, and image path.
 *
 * Validates the image path during initialization and assigns default values to bomb and fire.
 *
 * @param pos The position of the square as a pair (row, column).
 * @param player A pointer to the player occupying the square, if any.
 * @param squareType The type of square (e.g., Grass, Wall, UnbreakableWall).
 * @param imagePath The file path for the square's image.
 */
Square::Square(std::pair<int, int> pos, IPlayer* player, ESquareType squareType, std::string imagePath)
    : bomb(nullptr), fire(nullptr)
{
    this->position = pos;
    this->player = player;
    this->squareType = squareType;

    // Validate and assign image path
    if (Constants::isValidPath(imagePath)) {
        this->imagePath = imagePath;
    }
    else {
        std::cerr << "Image does not exist: " << imagePath << std::endl;
    }
}

/**
 * @brief Retrieves the position of the square.
 *
 * @return A pair representing the row and column of the square.
 */
std::pair<int, int> Square::GetPosition() const
{
    return position;
}

/**
 * @brief Checks if a player is present on the square.
 *
 * @return True if a player occupies the square, false otherwise.
 */
bool Square::HasPlayer() const
{
    return player != nullptr;
}

/**
 * @brief Retrieves the type of square.
 *
 * @return The square type (e.g., Grass, Wall, UnbreakableWall).
 */
ESquareType Square::GetSquareType() const
{
    return squareType;
}

/**
 * @brief Retrieves the player occupying the square, if any.
 *
 * @return A pointer to the player object, or nullptr if no player is present.
 */
IPlayer* Square::GetPlayer() const
{
    return player;
}

/**
 * @brief Retrieves the bomb placed on the square, if any.
 *
 * @return A pointer to the bomb object, or nullptr if no bomb is present.
 */
IBomb* Square::GetBomb() const
{
    return bomb;
}

/**
 * @brief Retrieves the fire effect on the square, if any.
 *
 * @return A pointer to the fire object, or nullptr if no fire is present.
 */
IFire* Square::GetFire() const
{
    return fire;
}

/**
 * @brief Retrieves the image path for the square.
 *
 * @return A string representing the file path to the square's image.
 */
std::string Square::GetImagePath() const
{
    return imagePath;
}

/**
 * @brief Sets a player on the square and updates the player's position.
 *
 * @param player A pointer to the player to be placed on the square.
 */
void Square::SetPlayer(IPlayer* player)
{
    this->player = player;
    this->player->SetPosition(this->position.first, this->position.second);
}

/**
 * @brief Sets a bomb on the square.
 *
 * @param bomb A pointer to the bomb object to be placed on the square.
 */
void Square::SetBomb(IBomb* bomb)
{
    this->bomb = bomb;
}

/**
 * @brief Sets a fire effect on the square.
 *
 * @param fire A pointer to the fire object to be set on the square.
 */
void Square::SetFire(IFire* fire)
{
    this->fire = fire;
}

/**
 * @brief Updates the image path for the square.
 *
 * @param imagePath A string representing the new file path to the square's image.
 */
void Square::SetImagePath(std::string imagePath)
{
    this->imagePath = imagePath;
}

/**
 * @brief Updates the type of the square.
 *
 * @param squareType The new square type (e.g., Grass, Wall, UnbreakableWall).
 */
void Square::SetSquareType(ESquareType squareType)
{
    this->squareType = squareType;
}

/**
 * @brief Removes the player from the square.
 */
void Square::RemovePlayer()
{
    player = nullptr;
}

/**
 * @brief Clears the bomb from the square and deallocates its memory.
 */
void Square::ClearBomb()
{
    if (bomb) {
        delete bomb;
        bomb = nullptr;
    }
}

/**
 * @brief Clears the fire effect from the square and deallocates its memory.
 */
void Square::ClearFire()
{
    if (fire) {
        delete fire;
        fire = nullptr;
    }
}

/**
 * @brief Checks if the square has a wall (specifically Grass square type).
 *
 * @return True if the square is a wall, false otherwise.
 */
bool Square::HasWall() const
{
    return squareType == ESquareType::Grass;
}

/**
 * @brief Checks if the square has a bomb.
 *
 * @return True if a bomb is present, false otherwise.
 */
bool Square::HasBomb() const
{
    return bomb != nullptr;
}

/**
 * @brief Checks if the square has fire.
 *
 * @return True if a fire effect is present, false otherwise.
 */
bool Square::HasFire() const
{
    return fire != nullptr;
}

/**
 * @brief Checks if the bomb on the square has exploded.
 *
 * @return True if the bomb has exploded, false otherwise.
 */
bool Square::HasBombExploded() const
{
    return this->bomb != nullptr && this->bomb->HasExploded();
}
