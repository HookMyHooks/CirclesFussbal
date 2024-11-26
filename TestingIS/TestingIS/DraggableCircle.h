#pragma once
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <cmath>

class DraggableCircle: public QGraphicsObject {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    DraggableCircle(qreal x, qreal y, qreal width, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;

    void setColor(const QColor& color);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    /// Updates position and handles collisions
    void updatePosition();

    /// Handles collision response
    void handleCollision(DraggableCircle* otherCircle);

    /// Apply an external force to the circle
    void applyImpulse(const QPointF& impulse) {
        m_velocity += impulse;
    }

private:
    qreal m_width, m_height;
    QColor m_color;
    QPointF m_velocity;
};
