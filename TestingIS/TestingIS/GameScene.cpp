#include "GameScene.h"
#include "QMessageBox"


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

void GameScene::SetLeftGoalPtr(QGraphicsRectItem* leftGoal)
{
    m_leftGoal = leftGoal;
}

void GameScene::SetRightGoalPtr(QGraphicsRectItem* rightGoal)
{
    m_rightGoal = rightGoal;
}

void GameScene::SetResetFunction(std::function<void(GameScene*)> ResetFunction)
{
    m_ResetFunction = ResetFunction;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (!isDragging) {
            QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
            activeCircle = dynamic_cast<DraggableCircle*>(item);
            
            //check if the clicked thing is ball first and disable functionality
            if (activeCircle && (activeCircle->isBall() || (m_game->GetCurrentPlayer() != activeCircle->GetPlayer())))
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

                m_game->SwitchPlayers();
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

bool GameScene::isBallInLeftGoal(const DraggableCircle* ball, const QPointF& topLeft, const QPointF& bottomLeft)
{
    // Ball's position
    qreal ballCenterX = ball->pos().x() + ball->boundingRect().width() / 2;
    qreal ballCenterY = ball->pos().y() + ball->boundingRect().height() / 2;

    // Check if the ball's center is within the goal's vertical range
    if (ballCenterY >= topLeft.y() && ballCenterY <= bottomLeft.y()) {
        // Check if the ball's center crosses the left edge
        if (ballCenterX <= topLeft.x()+ 30) {
            return true; // Ball is in the left goal
        }
    }
    return false;
}

bool GameScene::isBallInRightGoal(const DraggableCircle* ball, const QPointF& topRight, const QPointF& bottomRight)
{
    // Ball's position
    qreal ballCenterX = ball->pos().x() + ball->boundingRect().width() / 2;
    qreal ballCenterY = ball->pos().y() + ball->boundingRect().height() / 2;

    // Check if the ball's center is within the goal's vertical range
    if (ballCenterY >= topRight.y()&& ballCenterY <= bottomRight.y()) {
        // Check if the ball's center crosses the right edge
        if (ballCenterX >= topRight.x()-30) {
            return true; // Ball is in the right goal
        }
    }
    return false;
}

void GameScene::ResetBoard()
{


    /*m_ResetFunction(this);*/
    DraggableCircle* ball = nullptr;
    std::vector<DraggableCircle*> players;

	for (size_t i = 0; i < items().size(); i++)
	{
		this->removeItem(items().at(i));
	}
    DraggableCircle* redDef1 = new DraggableCircle(-80, -160, 60, false);
    DraggableCircle* redDef2 = new DraggableCircle(-80, 240, 60, false);
    DraggableCircle* redDef3 = new DraggableCircle(-80, 40, 60, false);
    redDef1->setColor(Qt::red);
    redDef2->setColor(Qt::red);
    redDef3->setColor(Qt::red);
    players.emplace_back(redDef1);
    players.emplace_back(redDef2);
    players.emplace_back(redDef3);
    //Att
    DraggableCircle* redAtt1 = new DraggableCircle(120, -80, 60, false);
    DraggableCircle* redAtt2 = new DraggableCircle(120, 160, 60, false);
    redAtt1->setColor(Qt::red);
    redAtt2->setColor(Qt::red);
    players.emplace_back(redAtt1);
    players.emplace_back(redAtt2);


    //Blue Team
    //Def
    DraggableCircle* blueAtt1 = new DraggableCircle(450, 160, 60, false);
    DraggableCircle* blueAtt2 = new DraggableCircle(450, -80, 60, false);
    blueAtt1->setColor(Qt::blue);
    blueAtt2->setColor(Qt::blue);
    players.emplace_back(blueAtt1);
    players.emplace_back(blueAtt2);
    //Att
    DraggableCircle* blueDef1 = new DraggableCircle(620, -180, 60, false);
    DraggableCircle* blueDef2 = new DraggableCircle(620, 40, 60, false);
    DraggableCircle* blueDef3 = new DraggableCircle(620, 240, 60, false);
    blueDef1->setColor(Qt::blue);
    blueDef2->setColor(Qt::blue);
    blueDef3->setColor(Qt::blue);
    players.emplace_back(blueDef1);
    players.emplace_back(blueDef2);
    players.emplace_back(blueDef3);
#pragma endregion

    //ball
    ball = new DraggableCircle(279, 79, 50, true);


    for (size_t i = 0; i < players.size(); i++)
    {
        this->addItem(players[i]);
        this->addItem(ball);
    }
}


void GameScene::updateCircles()
{
    for (QGraphicsItem* item : items()) {
        DraggableCircle* circle = dynamic_cast<DraggableCircle*>(item);
        if (circle) {
            if (circle->isBall())
            {
                QPointF leftTopLeft = m_leftGoal->mapToScene(m_leftGoal->boundingRect().topLeft());
                QPointF leftBottomLeft = m_leftGoal->mapToScene(m_leftGoal->boundingRect().bottomLeft());
                QPointF rightTopRight = m_rightGoal->mapToScene(m_rightGoal->boundingRect().topRight());
                QPointF rightBottomRight = m_rightGoal->mapToScene(m_rightGoal->boundingRect().bottomRight());

                // Check for a goal in the left goal area
                if (!m_leftGoalScored && isBallInLeftGoal(circle, leftTopLeft, leftBottomLeft)) {
                    QMessageBox mBox;
                    mBox.setText("Goal left side");
                    mBox.exec();
                    m_leftGoalScored = true;  // Mark left goal as scored
                    circle->freezePosition();  // Freeze the ball
                    //reset position and update using API 
                    //ResetBoard();
                    //return;
                }

                // Check for a goal in the right goal area
                if (!m_rightGoalScored && isBallInRightGoal(circle, rightTopRight, rightBottomRight)) {
                    QMessageBox mBox;
                    mBox.setText("Goal right side");
                    mBox.exec();
                    m_rightGoalScored = true; // Mark right goal as scored
                    circle->freezePosition();  // Freeze the ball
                    // reset position and update using API 
/*                    ResetBoard();
                    return*/;
                }


            }
            if (!m_rightGoalScored || !m_leftGoalScored)
                circle->updatePosition();
            //else
            //    ResetBoard();
        }
    }
}
