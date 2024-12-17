#include "Fire.h"
#include "Constants.h"

/**
 * @brief Constructs a Fire object with a specified position and timer.
 *
 * @param position The (x, y) coordinates representing the fire's position.
 * @param timer The duration (in seconds) for which the fire will persist.
 */
Fire::Fire(std::pair<int, int> position, float timer)
    : position{ position }, timer{ timer }
{
    imagePath = Constants::FirePNGPath;
}

/**
 * @brief Gets the position of the fire.
 *
 * @return A pair of integers representing the fire's (x, y) coordinates.
 */
std::pair<int, int> Fire::GetPosition() const
{
    return position;
}

/**
 * @brief Gets the remaining timer value for the fire.
 *
 * @return A float representing the time (in seconds) before the fire expires.
 */
float Fire::GetTimer() const
{
    return timer;
}

/**
 * @brief Gets the file path of the fire's image.
 *
 * @return A string representing the path to the fire's image file.
 */
std::string Fire::GetImagePath() const
{
    return imagePath;
}

/**
 * @brief Updates the fire's timer and checks if it has expired.
 *
 * Decreases the timer by the given elapsed time and determines whether the fire
 * has expired (timer reaches zero or below).
 *
 * @param elapsedTime The time (in seconds) to subtract from the fire's timer.
 * @return True if the fire has expired, false otherwise.
 */
bool Fire::HasExpired(const float& elapsedTime)
{
    timer -= elapsedTime;
    return timer <= 0.0f;
}
