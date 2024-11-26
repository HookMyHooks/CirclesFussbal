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

    
    DraggableCircle* circle1 = new DraggableCircle(50, 50, 50); // x, y, radius
    DraggableCircle* circle2 = new DraggableCircle(200, 200, 50);

    circle1->setColor(Qt::red);
    circle2->setColor(Qt::blue);

    scene->addItem(circle1);
    scene->addItem(circle2);

    // Create the view
    QGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setSceneRect(0, 0, 800, 600);
    view.show();

    return app.exec();
}