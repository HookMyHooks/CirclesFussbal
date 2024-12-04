#include "IFire.h"
#include <string>
#include <utility>
class Fire :public IFire {
private:
	std::pair<int, int> position;
	float timer;
	std::string imagePath;

public:

	Fire(std::pair<int, int> position, float timer);

	std::pair<int, int> GetPosition() const override;
	float GetTimer() const override;
	std::string GetImagePath() const override;
	bool HasExpired(const float& elapsedTime) override;

};