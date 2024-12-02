#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "PlayerObjects.h"
#include "TerrainObjects.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    auto game = IGame::Produce();


    GameScene* scene = new GameScene();
    scene->SetGame(game);
	scene->setSceneRect(-300, -300, 1200, 800);

    
    TerrainObjects terrain(scene);
    PlayerObjects player(scene);
    scene->SetResetFunction(std::bind(&PlayerObjects::ResetPositions, &player, scene));


    // Create the view
    QGraphicsView view(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setSceneRect(-300, -300, 1200, 800);
    view.show();

    return app.exec();
}