#pragma once
#include "ISquare.h"
#include <fstream>
class Square : public ISquare
{
public:
	Square(std::pair<int,int>pos,IPlayer* player , ESquareType squareType , std::string imagePath);
	~Square() = default;

	std::pair<int, int> GetPosition() const override;
	ESquareType GetSquareType() const override;
	IPlayer* GetPlayer() const override;
	IBomb* GetBomb() const override;
	IFire* GetFire() const override;
	std::string GetImagePath() const override;

	void SetPlayer(IPlayer* player) override;
	void SetBomb(IBomb* bomb) override;
	void SetFire(IFire* fire) override;
	void SetImagePath(std::string imagePath) override;
	void SetSquareType(ESquareType squareType) override;

	void RemovePlayer() override;
	void ClearBomb() override;
	void ClearFire() override;
	bool HasPlayer() const override;
	bool HasWall() const override;
	bool HasBomb() const override;
	bool HasFire() const override;
	bool HasBombExploded() const override;

private:

	std::pair<int, int> position;
	IPlayer* player;
	IBomb* bomb;
	IFire* fire;
	ESquareType squareType;
	std::string imagePath;
};

