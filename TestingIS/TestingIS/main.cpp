#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "DraggableCircle.h"  // Include your custom class

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GameScene* scene = new GameScene();
    QGraphicsView* view = new QGraphicsView(scene);

    // Create a draggable circle and add it to the scene
    DraggableCircle* circle1 = new DraggableCircle(100, 100, 50, 50);
    circle1->setColor(Qt::blue);
    scene->addItem(circle1);

    // Create the second circle
    DraggableCircle* circle2 = new DraggableCircle(200, 200, 50, 50);
    circle2->setColor(Qt::red);
    scene->addItem(circle2);

    // Set up the view
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->resize(800, 640);
    view->show();

    return app.exec();
}
