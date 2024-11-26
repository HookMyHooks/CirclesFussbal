#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "DraggableCircle.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr) : QGraphicsScene(parent) {
        // Timer to update positions continuously
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameScene::updateCircles);
        timer->start(16); // ~60 FPS
    }

protected:
    bool isDragging = false;
    QPointF initialMousePos;
    DraggableCircle* activeCircle = nullptr;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;



    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;


private slots:
    void updateCircles();
};
