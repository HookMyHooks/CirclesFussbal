#include "TerrainObjects.h"

TerrainObjects::TerrainObjects(GameScene* gameScene)
{
    // Draw a rectangle that matches the scene's borders
    borderRect = new QGraphicsRectItem(gameScene->sceneRect());
    borderRect->setPen(QPen(Qt::black, 5)); // Set the pen color and width
    borderRect->setBrush(QBrush(QColor("#1F4529"))); // Set the brush color to green
    gameScene->addItem(borderRect);

    // Draw a white line separating the two halves of the fussball table
    midX = gameScene->sceneRect().left() + gameScene->sceneRect().width() / 2;
    middleLine = new QGraphicsLineItem(midX, gameScene->sceneRect().top(), midX, gameScene->sceneRect().bottom());
    middleLine->setPen(QPen(Qt::white, 5)); // Set the pen color and width
    gameScene->addItem(middleLine);


    // Add a transparent ellipse with white edges in the middle of the scene
    midY = gameScene->sceneRect().top() + gameScene->sceneRect().height() / 2;
    middleEllipse = new QGraphicsEllipseItem(midX - 50, midY - 50, 100, 100); // x, y, width, height
    middleEllipse->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    middleEllipse->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    gameScene->addItem(middleEllipse);


    leftGoal = new QGraphicsRectItem(gameScene->sceneRect().left(), midY - goalHeight / 2, goalWidth, goalHeight);
    leftGoal->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    leftGoal->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    gameScene->SetLeftGoalPtr(leftGoal);
    gameScene->addItem(leftGoal);

    rightGoal = new QGraphicsRectItem(gameScene->sceneRect().right() - goalWidth, midY - goalHeight / 2, goalWidth, goalHeight);
    rightGoal->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    rightGoal->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    gameScene->SetRightGoalPtr(rightGoal);

    gameScene->addItem(rightGoal);

    
    leftBigRect = new QGraphicsRectItem(gameScene->sceneRect().left(), midY - bigRectHeight / 2, bigRectWidth, bigRectHeight);
    leftBigRect->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    leftBigRect->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    gameScene->addItem(leftBigRect);

    rightBigRect = new QGraphicsRectItem(gameScene->sceneRect().right() - bigRectWidth, midY - bigRectHeight / 2, bigRectWidth, bigRectHeight);
    rightBigRect->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    rightBigRect->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    gameScene->addItem(rightBigRect);
}
