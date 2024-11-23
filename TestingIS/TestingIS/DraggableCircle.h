#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>
#include <cmath>
#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QPainter>

class DraggableCircle : public QGraphicsObject {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Define pos as a Q_PROPERTY to allow QPropertyAnimation to animate it


/// <summary>
/// Inherits from QGraphicsObject => combines the functionality of QObject and QGraphicsItem
/// Needed for PropertyAnimation
/// </summary>

public:
    DraggableCircle(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr)
        : QGraphicsObject(parent), m_width(width), m_height(height) {
        setPos(x, y); // Set the initial position
    }

    /// <summary>
    /// Specifies the clickable area of the circle 
    /// </summary>
    QRectF boundingRect() const override {
        return QRectF(0, 0, m_width, m_height); // Defines the area of the circle
    }


    void setColor(const QColor color)
    {
        m_color = color;
        update();
    }


    //might need to change to UI - get the color and redraw it

    /// <summary>
    /// Since QGraphicsItem doesn't draw anything by default, we use QPainter to draw the circle 
    /// </summary>
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override {
        painter->setBrush(m_color);  // Fill the circle with blue color
        painter->drawEllipse(0, 0, m_width, m_height); // Draw the circle
    }

    void applyImpulse(const QPointF& impulse) {
        QPointF targetPos = pos() + impulse;

        QGraphicsScene* scene = this->scene();
        if (scene) {
            // Check for collisions
            for (QGraphicsItem* item : scene->items()) {
                if (item != this) {
                    DraggableCircle* otherCircle = dynamic_cast<DraggableCircle*>(item);
                    if (otherCircle) {
                        // Calculate distance between the centers
                        qreal dx = targetPos.x() + m_width / 2 - (otherCircle->x() + otherCircle->m_width / 2);
                        qreal dy = targetPos.y() + m_height / 2 - (otherCircle->y() + otherCircle->m_height / 2);
                        qreal distance = qSqrt(dx * dx + dy * dy);

                        // Check if circles overlap
                        qreal combinedRadii = m_width / 2 + otherCircle->m_width / 2;
                        if (distance < combinedRadii) {
                            qDebug() << "Collision detected before overlap!";
                            return; // Stop movement
                        }
                    }
                }
            }
        }
        animateTo(targetPos); // Animate to the new position
        //qDebug() << "Applied impulse:" << impulse << "Target position:" << targetPos;
    }

private:
    qreal m_width, m_height;
    QColor m_color;

    /// <summary>
    /// Animate the transition of the circle
    /// </summary>
    /// <param name="targetPos"></param>
    void animateTo(const QPointF& targetPos) {
        QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
        animation->setDuration(500); // Adjust the duration as needed
        animation->setStartValue(pos());
        animation->setEndValue(targetPos);
        animation->setEasingCurve(QEasingCurve::OutQuad); // Smooth out the movement
        animation->start(QAbstractAnimation::DeleteWhenStopped); // Automatically clean up
    }
};


// Custom scene to handle global mouse clicks
class GameScene : public QGraphicsScene {
public:
    GameScene(QObject* parent = nullptr) : QGraphicsScene(parent) {}

protected:
    bool isDragging = false;         // Tracks if we're in "drag-and-release" mode
    QPointF initialMousePos;         // Stores the first click position
    DraggableCircle* activeCircle = nullptr;  // Tracks which circle is being dragged

    // Handle mouse press events at the scene level
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            if (!isDragging) {
                // First click: Check if a circle was clicked
                QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
                activeCircle = dynamic_cast<DraggableCircle*>(item);

                if (activeCircle) {
                    isDragging = true;  // Start drag-and-release mode
                    initialMousePos = event->scenePos();  // Store the initial position
                    activeCircle->setCursor(Qt::ClosedHandCursor);  // Indicate selection
                    //qDebug() << "Drag started at:" << initialMousePos;
                }
            }
            else {
                // Second click: End drag and calculate impulse
                if (activeCircle) {
                    QPointF finalMousePos = event->scenePos();  // Get final mouse position
                    QPointF impulse = initialMousePos - finalMousePos;  // Calculate impulse


                    

                    // Limit the impulse magnitude (optional)
                    const double maxSpeed = 300.0;  // Max speed limit
                    double magnitude = std::sqrt(impulse.x() * impulse.x() + impulse.y() * impulse.y());
                    if (magnitude > maxSpeed) {
                        impulse *= maxSpeed / magnitude;  // Scale down to max speed
                    }

                    activeCircle->applyImpulse(impulse);  // Apply impulse to the circle
                    activeCircle->setCursor(Qt::OpenHandCursor);  // Reset cursor

                    // Reset state
                    isDragging = false;
                    activeCircle = nullptr;
                    //qDebug() << "Drag ended at:" << finalMousePos << "Impulse:" << impulse;
                }
            }
        }

        QGraphicsScene::mousePressEvent(event);  // Propagate event
    }

    // Optional: Reset cursor when mouse leaves the scene
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        if (activeCircle) {
            activeCircle->setCursor(Qt::ArrowCursor);  // Reset cursor when mouse is released
        }
        QGraphicsScene::mouseReleaseEvent(event);
    }
};
