#include "GameScene.h"



/// <summary>
/// Handles mouse press events at the scene level to enable a drag-and-release movement
/// mechanic for draggable circles. This method determines whether the user has clicked
/// on a circle and initiates or ends the drag-and-release operation.
/// </summary>
/// <param name="event">
/// The mouse event containing information about the click, such as the position
/// and mouse button used.
/// </param>
/// <remarks>
/// - On the first click, it detects if a circle was clicked and enters "drag" mode,
///   storing the initial position of the mouse.
/// - On the second click, it calculates an impulse vector based on the drag distance
///   and applies the force to the selected circle.
/// - This method also manages cursor state changes for user feedback.
/// </remarks>
/// <example>
/// // Example usage:
/// // Clicking on a circle and dragging will simulate an impulse:
/// GameScene* scene = new GameScene();
/// scene->mousePressEvent(new QGraphicsSceneMouseEvent());
/// </example>

void GameScene::SetGame(std::shared_ptr<IGame> game)
{
    m_game = game;
}

void GameScene::OnWin()
{
    //win msg
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (!isDragging) {
            QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
            activeCircle = dynamic_cast<DraggableCircle*>(item);
            //check if the clicked thing is ball first and disable functionality
            if (activeCircle->isBall())
            {
                activeCircle = nullptr;
                return;
            }

            if (activeCircle) {
                isDragging = true;
                initialMousePos = event->scenePos();
                //activeCircle->setCursor(Qt::ClosedHandCursor); // Set cursor using Qt::CursorShape
            }
        }
        else {
            if (activeCircle) {
                QPointF finalMousePos = event->scenePos();
                QPointF impulse = initialMousePos - finalMousePos;

                // Limit the impulse magnitude
                const double maxSpeed = 20.0;
                double magnitude = std::sqrt(impulse.x() * impulse.x() + impulse.y() * impulse.y());
                if (magnitude > maxSpeed) {
                    impulse *= maxSpeed / magnitude;
                }

                activeCircle->applyImpulse(impulse);
                //activeCircle->setCursor(Qt::OpenHandCursor); // Set cursor using Qt::CursorShape

                isDragging = false;
                activeCircle = nullptr;
            }
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (activeCircle) {
        //activeCircle->setCursor(Qt::CursorShape::ArrowCursor);
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void GameScene::updateCircles()
{
    for (QGraphicsItem* item : items()) {
        DraggableCircle* circle = dynamic_cast<DraggableCircle*>(item);
        if (circle) {
            circle->updatePosition();
        }
    }
}
