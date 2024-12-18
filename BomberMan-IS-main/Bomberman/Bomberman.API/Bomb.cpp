#include "Bomb.h"

/**
 * @brief Constructs a Bomb object with a given position, range, and timer.
 *
 * @param position The (x, y) coordinates representing the bomb's position.
 * @param range The explosion range of the bomb.
 * @param timer The countdown timer until the bomb explodes.
 */
Bomb::Bomb(std::pair<int, int> position, int range, float timer)
    : position(position), range(range), timer(timer)
{
    imagePath = Constants::BombPNGPath;
    if (!Constants::isValidPath(imagePath)) {
        std::cerr << "Image does not exist: " << imagePath << std::endl;
    }
}

/**
 * @brief Gets the position of the bomb.
 *
 * @return A pair of integers representing the bomb's (x, y) coordinates.
 */
std::pair<int, int> Bomb::GetPosition() const
{
    return position;
}

/**
 * @brief Gets the explosion range of the bomb.
 *
 * @return The explosion range as an integer.
 */
int Bomb::GetRange() const
{
    return range;
}

/**
 * @brief Gets the file path of the bomb's image.
 *
 * @return A string representing the path to the bomb's image file.
 */
std::string Bomb::GetImagePath() const
{
    return imagePath;
}

/**
 * @brief Sets the file path of the bomb's image.
 *
 * @param path A string representing the new path to the bomb's image file.
 */
void Bomb::SetImagePath(const std::string& path)
{
    imagePath = path;
}

/**
 * @brief Checks if the bomb has exploded.
 *
 * @return True if the bomb's timer has reached zero or below, otherwise false.
 */
bool Bomb::HasExploded() const
{
    return timer <= 0;
}

/**
 * @brief Updates the bomb's timer based on elapsed time.
 *
 * @param elapsedTime The amount of time (in seconds) to subtract from the timer.
 */
void Bomb::UpdateTimer(float elapsedTime)
{
    timer -= elapsedTime;
}
