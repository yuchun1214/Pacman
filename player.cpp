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
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));

    this->setPos(QPointF(COORDINATE_SCALE * startPoint.x() - PLAYER_EDGE / 2,COORDINATE_SCALE * startPoint.y() - PLAYER_EDGE / 2));
    this->setRect(0 , 0 , PLAYER_EDGE, PLAYER_EDGE);
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
}

void Player::move(){

    QPointF tempPos;
    int putInToStackAmounts = 0;
//    graphArray[int((this->pos().x() + PLAYER_EDGE / 2) / COORDINATE_SCALE)][int((this->pos().y() + PLAYER_EDGE / 2) / COORDINATE_SCALE)] = true;

    for(int i = 0, size = movingVectors.size(); i < size; ++i){
        tempPos = QPointF(this->pos().x() + PLAYER_EDGE / 2 + movingVectors[i].x(), this->pos().y() + PLAYER_EDGE / 2 + movingVectors[i].y());
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
    if(!graphArray[int((this->pos().x() + PLAYER_EDGE / 2) / COORDINATE_SCALE)][int((this->pos().y() + PLAYER_EDGE / 2) / COORDINATE_SCALE)]){
        graphArray[int((this->pos().x() + PLAYER_EDGE / 2) / COORDINATE_SCALE)][int((this->pos().y() + PLAYER_EDGE / 2) / COORDINATE_SCALE)] = true;
    }

    QColor color(Qt::gray);
    if(putInToStackAmounts > 1){
        color.setRed(Qt::red);
        vertices.append(tempVertex);
        tempVertex = new Vertex(this->scene,color);
        this->tempVertex->addDots(QPointF(this->pos().x() + PLAYER_EDGE / 2, this->pos().y() + PLAYER_EDGE / 2));
        flag = true;
    }else if(!putInToStackAmounts){ // means that the point is the end of the vertex;
        this->tempVertex->addDots(QPointF(this->pos().x() + PLAYER_EDGE / 2, this->pos().y() + PLAYER_EDGE / 2));
        vertices.append(tempVertex);
        tempVertex = new Vertex(this->scene,PlayerParms::DotColors[vertices.size() % PlayerParms::DotColors.size()]);
    }else{
        if(flag){
            this->tempVertex->addDots(QPointF(this->pos().x() + PLAYER_EDGE / 2, this->pos().y() + PLAYER_EDGE / 2));
            vertices.append(tempVertex);
            tempVertex = new Vertex(this->scene,PlayerParms::DotColors[vertices.size() % PlayerParms::DotColors.size()]);
            flag = false;
        }
        this->tempVertex->addDots(QPointF(this->pos().x() + PLAYER_EDGE / 2, this->pos().y() + PLAYER_EDGE / 2));
    }


    // pop up
    if(!backTrackStack.size()){
        disconnect(this->timer,SIGNAL(timeout()),this,SLOT(move()));
        vertices.append(tempVertex);
        emit dotFinish();
        return;
    }
    else{
        QPointF newPos;
        do{
            if(backTrackStack.isEmpty())
                break;
            newPos = backTrackStack.last();
            this->setPos(QPointF(newPos.x() - PLAYER_EDGE / 2, newPos.y() - PLAYER_EDGE / 2));
            backTrackStack.pop_back();
        }while(graphArray[int((this->pos().x() + PLAYER_EDGE / 2) / COORDINATE_SCALE)][int((this->pos().y() + PLAYER_EDGE / 2) / COORDINATE_SCALE)]);
    }
}

QVector<Vertex *> Player::Vertices(){
    return vertices;
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
