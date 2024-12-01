#pragma once
#include "GameScene.h"
class TerrainObjects
{
public:
	TerrainObjects(GameScene* gameScene);


private:
	qreal goalWidth = 100;
	qreal goalHeight = 200;
	QGraphicsRectItem* borderRect;
	QGraphicsLineItem* middleLine;
	qreal midX;
	qreal midY;
	QGraphicsEllipseItem* middleEllipse;
	QGraphicsRectItem* leftGoal;
	QGraphicsRectItem* rightGoal;
	QGraphicsRectItem* leftBigRect;
	QGraphicsRectItem* rightBigRect;

};

