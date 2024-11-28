#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "DraggableCircle.h"  
#include "GameScene.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    auto game = IGame::Produce();


    GameScene* scene = new GameScene();
    scene->SetGame(game);
	scene->setSceneRect(-300, -300, 1200, 800);

    // Draw a rectangle that matches the scene's borders
    QGraphicsRectItem* borderRect = new QGraphicsRectItem(scene->sceneRect());
    borderRect->setPen(QPen(Qt::black, 5)); // Set the pen color and width
    borderRect->setBrush(QBrush(Qt::green)); // Set the brush color to green
    scene->addItem(borderRect);

	// Draw a white line separating the two halves of the fussball table
    qreal midX = scene->sceneRect().left() + scene->sceneRect().width() / 2;
    QGraphicsLineItem* middleLine = new QGraphicsLineItem(midX, scene->sceneRect().top(), midX, scene->sceneRect().bottom());
    middleLine->setPen(QPen(Qt::white, 5)); // Set the pen color and width
    scene->addItem(middleLine);


    // Add a transparent ellipse with white edges in the middle of the scene
    qreal midY = scene->sceneRect().top() + scene->sceneRect().height() / 2;
    QGraphicsEllipseItem* middleEllipse = new QGraphicsEllipseItem(midX - 50, midY - 50, 100, 100); // x, y, width, height
    middleEllipse->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    middleEllipse->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    scene->addItem(middleEllipse);

    qreal goalWidth = 100;
    qreal goalHeight = 200;
    QGraphicsRectItem* leftGoal = new QGraphicsRectItem(scene->sceneRect().left(), midY - goalHeight / 2, goalWidth, goalHeight);
    leftGoal->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    leftGoal->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    scene->addItem(leftGoal);

    QGraphicsRectItem* rightGoal = new QGraphicsRectItem(scene->sceneRect().right() - goalWidth, midY - goalHeight / 2, goalWidth, goalHeight);
    rightGoal->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    rightGoal->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    scene->addItem(rightGoal);

    qreal bigRectWidth = 150;
    qreal bigRectHeight = 300;
    QGraphicsRectItem* leftBigRect = new QGraphicsRectItem(scene->sceneRect().left(), midY - bigRectHeight / 2, bigRectWidth, bigRectHeight);
    leftBigRect->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    leftBigRect->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    scene->addItem(leftBigRect);

    QGraphicsRectItem* rightBigRect = new QGraphicsRectItem(scene->sceneRect().right() - bigRectWidth, midY - bigRectHeight / 2, bigRectWidth, bigRectHeight);
    rightBigRect->setPen(QPen(Qt::white, 5)); // Set the pen color to white and width
    rightBigRect->setBrush(QBrush(Qt::transparent)); // Set the brush color to transparent
    scene->addItem(rightBigRect);


    DraggableCircle* circle1 = new DraggableCircle(50, 50, 50); // x, y, radius
    DraggableCircle* circle2 = new DraggableCircle(200, 200, 50);

    circle1->setColor(Qt::red);
    circle2->setColor(Qt::blue);



    scene->addItem(circle1);
    scene->addItem(circle2);



    // Create the view
    QGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setSceneRect(-300, -300, 1200, 800);
    view.show();

    return app.exec();
}