#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "DraggableCircle.h"
#include "IGame.h"

class GameScene : public QGraphicsScene, public IGameListener {
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr) : QGraphicsScene(parent) {
        // Timer to update positions continuously
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameScene::updateCircles);
        timer->start(16); // ~60 FPS
    }


    void SetGame(std::shared_ptr<IGame> game);

    void OnWin() override;

    void SetLeftGoalPtr(QGraphicsRectItem* leftGoal);
    void SetRightGoalPtr(QGraphicsRectItem* rightGoal);

    void SetResetFunction(std::function<void(GameScene*)> ResetFunction);

protected:
    bool isDragging = false;
    QPointF initialMousePos;
    DraggableCircle* activeCircle = nullptr;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;



    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;


private slots:
    void updateCircles();

private:
    std::shared_ptr<IGame> m_game;
    QGraphicsRectItem* m_leftGoal = nullptr;
    QGraphicsRectItem* m_rightGoal = nullptr;
    std::function<void(GameScene*)> m_ResetFunction;

    bool m_leftGoalScored = false;  // Tracks if a left-side goal has been scored
    bool m_rightGoalScored = false; // Tracks if a right-side goal has been scored



    bool isBallInLeftGoal( const DraggableCircle* ball, const QPointF& topLeft, const QPointF& bottomLeft);
    bool isBallInRightGoal(const DraggableCircle* ball, const QPointF& topRight, const QPointF& bottomRight);

    void ResetBoard();

};
