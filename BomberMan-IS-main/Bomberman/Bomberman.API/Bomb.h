#pragma once
#include "IBomb.h"
#include "Constants.h"
#include <iostream>
class Bomb : public IBomb {
private:
	std::pair<int, int> position;
	float timer;
	int range;
	std::string imagePath;

public:

	//Constructor
	Bomb(std::pair<int, int> position, int range,float timer);

	//Getters
	std::pair<int, int> GetPosition() const override;
	int GetRange() const override;
    std::string GetImagePath() const override;

	//Setters
	void SetImagePath(const std::string& path) override;
	bool HasExploded() const override;
	void UpdateTimer(float elapsedTime) override;

};