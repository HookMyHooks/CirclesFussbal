#pragma once
#include <utility>
#include <string>
class IBomb {
public:
	virtual ~IBomb()=default;

	//Getters
	virtual std::pair<int,int> GetPosition() const = 0;
	virtual int GetRange() const = 0;
	virtual std::string GetImagePath() const = 0;

	//Setters
	virtual void SetImagePath(const std::string& imagePath) = 0;
	virtual bool HasExploded() const = 0;
	virtual void UpdateTimer(float elapsedTime) = 0;
};