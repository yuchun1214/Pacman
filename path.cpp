#include "path.h"

Path::Path(QObject *parent) : QObject(parent)
{

}


Path::Path(QPoint startPoint, QGraphicsScene * scene, QObject * parent) : QObject (parent), QGraphicsRectItem (){

}

QPoint Path::giveMePath(QPoint startPos, QPoint targetPos){
    QPoint movingVector;
    this->judgeMovingVector(startPos,targetPos,&QPoint::x, &QPoint::setX,movingVector);
    this->judgeMovingVector(startPos,targetPos,&QPoint::y, &QPoint::setY,movingVector);
    return movingVector;
}

QPoint Path::judgeMovingVector(QPoint startPos, QPoint targetPos, int (QPoint::*coordinate)() const, void (QPoint::*setCoordinate)(int), QPoint &movingVector){
    int tc = (targetPos.*coordinate)(), sc = (startPos.*coordinate)();
    if(tc > sc){
        (movingVector.*setCoordinate)(1);
    }else if(tc == sc){
        (movingVector.*setCoordinate)(0);
    }else{
        (movingVector.*setCoordinate)(-1);
    }
    return movingVector;
}
