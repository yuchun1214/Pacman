#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

Player::Player(QPoint startPoint,QGraphicsScene * scene, QObject * parent):
    QObject (parent),
    QGraphicsRectItem (),
    movingVectorPX(COORDINATE_SCALE, 0),
    movingVectorNX(-COORDINATE_SCALE,0),
    movingVectorPY(0,COORDINATE_SCALE),
    movingVectorNY(0,-COORDINATE_SCALE)
{
    this->timer = new QTimer();
    this->scene = scene;
    timer->start(50);
    this->setPos(QPointF(COORDINATE_SCALE * startPoint.x() - PLAYER_EDGE / 2,COORDINATE_SCALE * startPoint.y() - PLAYER_EDGE / 2));
    this->setRect(0 , 0 , PLAYER_EDGE, PLAYER_EDGE);
    scene->addItem(this);
    for(int i = 0; i < MAZE_WIDTH + 1; ++i){
        for(int j = 0; j < MAZE_HEIGHT + 1; ++j){
            graphArray[i][j] = 0;
        }
    }
//    this->setPos(QPointF(this->rect().x() + PLAYER_EDGE / 2, this->rect().y() + PLAYER_EDGE / 2));
    graphArray[int(this->pos().x() / PLAYER_EDGE)][int(this->pos().y() / PLAYER_EDGE)] = 1;
    movingVectors.push_back(movingVectorPX);
    movingVectors.push_back(movingVectorPY);
    movingVectors.push_back(movingVectorNX);
    movingVectors.push_back(movingVectorNY);
//    qDebug()<<"newly pos"<<QPointF(this->rect().x() + PLAYER_EDGE / 2, this->rect().y() + PLAYER_EDGE / 2);

    connect(timer, SIGNAL(timeout()),this,SLOT(move()));

}

void Player::move(){
    // pushback
//    qDebug()<<"\n\nIn move";
//    qDebug()<<"this->pos"<<this->pos();
    graphArray[int((this->pos().x() + PLAYER_EDGE / 2) / COORDINATE_SCALE)][int((this->pos().y() + PLAYER_EDGE / 2) / COORDINATE_SCALE)] = true;
    bool flag = false;
    QPointF tempPos;
//    qDebug()<<movingVectors;
    for(int i = 0, size = movingVectors.size(); i < size; ++i){
        tempPos = QPointF(this->pos().x() + PLAYER_EDGE / 2 + movingVectors[i].x(), this->pos().y() + PLAYER_EDGE / 2 + movingVectors[i].y());
//        qDebug()<<"tempPos" << tempPos;
//        qDebug()<<"this->scene->items(tempPos).size()"<<this->scene->items(tempPos).size();
//        qDebug()<<"scene->items(tempPos);"<<scene->items(tempPos);
        if(scene->items(tempPos).size() < BARRIER_CHECK_NUM){
//            qDebug()<<int(tempPos.x() / COORDINATE_SCALE) <<" , "<<int(tempPos.y() / COORDINATE_SCALE);
            if(!graphArray[int(tempPos.x() / COORDINATE_SCALE)][int(tempPos.y() / COORDINATE_SCALE)]){
//                flag = true;
//                qDebug()<<"push_back(tempPos);"<<tempPos;
                backTrackStack.push_back(tempPos);
            }
        }
    }
//    qDebug()<<backTrackStack;
    if(flag){
        showGraphArray();
    }
    // pop up
    if(!backTrackStack.size()){
        disconnect(this->timer,SIGNAL(timeout()),this,SLOT(move()));
        return;
    }
    else{
        QPointF newPos = backTrackStack.last();
        this->setPos(QPointF(newPos.x() - PLAYER_EDGE / 2, newPos.y() - PLAYER_EDGE / 2));
        Dot * dot = new Dot(newPos);
        this->scene->addItem(dot);
        backTrackStack.pop_back();
    }
//    qDebug()<<"============================end move=======================\n\n";
}

void Player::showGraphArray(){
    QDebug deb = qDebug();
    for(int i = 1; i < MAZE_WIDTH + 1; ++i){
        for(int j = 1; j < MAZE_HEIGHT; ++j){
            deb.nospace()<<this->graphArray[i][j];
        }
        qDebug()<<"\n";
    }
}
