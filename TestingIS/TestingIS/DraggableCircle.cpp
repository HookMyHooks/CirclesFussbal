#include "DraggableCircle.h"

DraggableCircle::DraggableCircle(qreal x, qreal y, qreal width, QGraphicsItem* parent)
    : QGraphicsObject(parent), m_width(width), m_height(width) {
    setPos(x, y);
    m_velocity = QPointF(0, 0);
}



/// <summary>
/// Defines the bounding rectangle of the circle item.
/// This rectangle specifies the clickable and drawable area for the circle,
/// which is required for collision detection and rendering.
/// </summary>
/// <returns>
/// A QRectF representing the bounds of the circle in local coordinates.
/// The rectangle's dimensions are equal to the width and height of the circle.
/// </returns>

QRectF DraggableCircle::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);

}

void DraggableCircle::setColor(const QColor& color)
{
    m_color = color;
    update();
}

void DraggableCircle::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setBrush(m_color);
    painter->drawEllipse(0, 0, m_width, m_height);
}




/// <summary>
/// Updates the position of the circle in the scene based on its current velocity or
/// any external factors (e.g., impulse or animation). This method ensures that the
/// circle respects the scene boundaries and avoids overlapping with other items.
/// </summary>
/// <remarks>
/// This method can be used to integrate physics, collision detection, or smooth
/// animations when moving the circle within the scene.
/// </remarks>
void DraggableCircle::updatePosition()
{
    QPointF newPos = pos() + m_velocity;

    QGraphicsScene* scene = this->scene();
    if (scene) {
        for (QGraphicsItem* item : scene->items()) {
            if (item != this) {
                DraggableCircle* otherCircle = dynamic_cast<DraggableCircle*>(item);
                if (otherCircle) {
                    // Collision detection
                    qreal dx = newPos.x() + m_width / 2 - (otherCircle->x() + otherCircle->m_width / 2);
                    qreal dy = newPos.y() + m_height / 2 - (otherCircle->y() + otherCircle->m_height / 2);
                    qreal distance = std::sqrt(dx * dx + dy * dy);

                    qreal combinedRadii = m_width / 2 + otherCircle->m_width / 2;
                    if (distance < combinedRadii) {
                        handleCollision(otherCircle);
                        return; // Exit to prevent invalid state
                    }
                }
            }
        }
    }

    // Apply friction to velocity
    m_velocity *= 0.9;

    // Update position
    setPos(newPos);
}

void DraggableCircle::handleCollision(DraggableCircle* otherCircle)
{
    // Calculate collision vector
    QPointF collisionVector = pos() - otherCircle->pos();
    qreal distance = std::sqrt(collisionVector.x() * collisionVector.x() +
        collisionVector.y() * collisionVector.y());
    QPointF collisionNormal = collisionVector / distance;

    // Relative velocity
    QPointF relativeVelocity = m_velocity - otherCircle->m_velocity;

    // Velocity along the normal
    qreal velocityAlongNormal = QPointF::dotProduct(relativeVelocity, collisionNormal);

    // Ignore if moving away
    if (velocityAlongNormal > 0) return;

    // Calculate impulse
    qreal restitution = 1.0; // Perfectly elastic collision
    qreal impulseMagnitude = -(1 + restitution) * velocityAlongNormal / 2; // Equal mass

    QPointF impulse = impulseMagnitude * collisionNormal;

    // Update velocities
    m_velocity += impulse;
    otherCircle->m_velocity -= impulse;

    // Resolve overlap
    qreal overlap = (m_width / 2 + otherCircle->m_width / 2) - distance;
    QPointF correction = collisionNormal * (overlap / 2);
    setPos(pos() + correction);
    otherCircle->setPos(otherCircle->pos() - correction);
}
