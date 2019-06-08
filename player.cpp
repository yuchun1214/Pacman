#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

Player::Player(QPoint startPoint,QGraphicsScene * scene,Path * path, QObject * parent):
    QObject (parent),
    QGraphicsRectItem (),
    movingVectorPX(COORDINATE_SCALE, 0),
    movingVectorNX(-COORDINATE_SCALE,0),
    movingVectorPY(0,COORDINATE_SCALE),
    movingVectorNY(0,-COORDINATE_SCALE),
    currentMovingVector(0,0),
    lastMovingVector(0,0)
{
    this->timer = new QTimer();
    this->scene = scene;
    timer->start(10);
    if(DEPLOY_DOTS){
        connect(timer, SIGNAL(timeout()),this,SLOT(deployDots()));
    }
//    timer = new QTimer();


    this->setPos(startPoint * COORDINATE_SCALE);
    this->setRect(- PLAYER_EDGE / 2 , - PLAYER_EDGE / 2 , PLAYER_EDGE, PLAYER_EDGE);
    scene->addItem(this);
    for(int i = 0; i < MAZE_WIDTH + 1; ++i){
        for(int j = 0; j < MAZE_HEIGHT + 1; ++j){
            graphArray[i][j] = 0;
        }
    }
    movingVectors.push_back(movingVectorPX);
    movingVectors.push_back(movingVectorPY);
    movingVectors.push_back(movingVectorNX);
    movingVectors.push_back(movingVectorNY);


    tempVertex = new Vertex(scene);
    this->flag = false;
    this->path = path;
}

void Player::deployDots(){

    QPointF tempPos;
    int putInToStackAmounts = 0;
//    graphArray[int((this->pos().x() + PLAYER_EDGE / 2) / COORDINATE_SCALE)][int((this->pos().y() + PLAYER_EDGE / 2) / COORDINATE_SCALE)] = true;

    for(int i = 0, size = movingVectors.size(); i < size; ++i){
        tempPos = QPointF(this->pos().x() + movingVectors[i].x(), this->pos().y() + movingVectors[i].y());
//        qDebug()<<"tempPos"<<tempPos;
        if(scene->items(tempPos).size() < BARRIER_CHECK_NUM){
            if(!graphArray[int(tempPos.x() / COORDINATE_SCALE)][int(tempPos.y() / COORDINATE_SCALE)]){
                ++putInToStackAmounts;
//                qDebug()<<"getInToStack"<<tempPos;
                backTrackStack.push_back(tempPos);
            }
        }
    }

    // set the current point to correct state;
    if(!graphArray[int((this->pos().x()) / COORDINATE_SCALE)][int((this->pos().y()) / COORDINATE_SCALE)]){
        graphArray[int((this->pos().x()) / COORDINATE_SCALE)][int((this->pos().y()) / COORDINATE_SCALE)] = true;
    }

    QColor color(Qt::gray);
    if(putInToStackAmounts > 1){
        color.setRed(Qt::red);
        vertices.append(tempVertex);
        tempVertex = new Vertex(this->scene,color);
        this->tempVertex->addDots(QPointF(this->pos().x(), this->pos().y()));
        flag = true;
    }else if(!putInToStackAmounts){ // means that the point is the end of the vertex;
        this->tempVertex->addDots(QPointF(this->pos().x(), this->pos().y()));
        vertices.append(tempVertex);
        tempVertex = new Vertex(this->scene,PlayerParms::DotColors[vertices.size() % PlayerParms::DotColors.size()]);
    }else{
        if(flag){
            this->tempVertex->addDots(QPointF(this->pos().x(), this->pos().y()));
            vertices.append(tempVertex);
            tempVertex = new Vertex(this->scene,PlayerParms::DotColors[vertices.size() % PlayerParms::DotColors.size()]);
            flag = false;
        }
        this->tempVertex->addDots(QPointF(this->pos().x(), this->pos().y()));
    }


    // pop up
    if(!backTrackStack.size()){
        disconnect(this->timer,SIGNAL(timeout()),this,SLOT(deployDots()));
        vertices.append(tempVertex);
        timer->start(100);
        connect(timer, SIGNAL(timeout()),this,SLOT(move()));
        emit dotFinish();
        return;
    }
    else{
        QPointF newPos;
        do{
            if(backTrackStack.isEmpty())
                break;
            newPos = backTrackStack.last();
            this->setPos(QPointF(newPos.x(), newPos.y()));
            backTrackStack.pop_back();
        }while(graphArray[int((this->pos().x()) / COORDINATE_SCALE)][int((this->pos().y()) / COORDINATE_SCALE)]);
    }
}

QVector<Vertex *> Player::Vertices(){
    return vertices;
}

void Player::moveTo(QPoint target){

    int maxTimes = 9;
    int i = 0;
    while (this->tinyCoordinate(this->pos()) != target && ++i < maxTimes) {
        QPoint movingVector;
        movingVector = path->giveMePath(this->tinyCoordinate(this->pos()),this->tinyCoordinate(target));
        qDebug()<<"movingVector = "<<movingVector;
        movingVector = this->BigCoordinate(movingVector);
        movingVector += QPoint(int(this->pos().x()),int(this->pos().y()));
        setPos(movingVector);
    }

}

QPoint Player::tinyCoordinate(QPoint target){
    return QPoint(target.x()/COORDINATE_SCALE, target.y() / COORDINATE_SCALE);
}

QPoint Player::tinyCoordinate(QPointF target){
     return QPoint(target.x()/COORDINATE_SCALE, target.y() / COORDINATE_SCALE);
}

QPoint Player::BigCoordinate(QPoint c){
    return QPoint(c.x() * COORDINATE_SCALE, c.y() * COORDINATE_SCALE);
}

void Player::keyPressEvent(QKeyEvent *event){
    lastMovingVector = currentMovingVector;
    if(event->key() == Qt::Key::Key_Up){
        currentMovingVector.setX(0);
        currentMovingVector.setY(-1);

        qDebug()<<"up";
    }else if(event->key() == Qt::Key::Key_Down){
        currentMovingVector.setX(0);
        currentMovingVector.setY(1);
        qDebug()<<"Down";
    }else if(event->key() == Qt::Key::Key_Left){
        currentMovingVector.setX(-1);
        currentMovingVector.setY(0);
        qDebug()<<"Left";
    }else if(event->key() == Qt::Key::Key_Right){
        currentMovingVector.setX(1);
        currentMovingVector.setY(0);
        qDebug()<<"Right";
    }
    QPointF temp = this->pos() + currentMovingVector * COORDINATE_SCALE;
    QList<QGraphicsItem *> items =  this->scene->items(temp);
    QGraphicsItem * tempItem;
    if(items.size()){
        tempItem = items[0];
        if(typeid(*tempItem) == typeid(Barrier)){
            currentMovingVector = lastMovingVector;
        }
    }

}

void Player::move(){
    QPointF temp = this->pos() + currentMovingVector * COORDINATE_SCALE;
    QList<QGraphicsItem *> items =  this->scene->items(temp);
    QGraphicsItem * tempItem;
    if(items.size()){
        tempItem = items[0];
        if(typeid(*tempItem) == typeid(Barrier)){
            currentMovingVector.setX(0);
            currentMovingVector.setY(0);
        }
    }
    setPos(pos() + currentMovingVector * COORDINATE_SCALE);
}
