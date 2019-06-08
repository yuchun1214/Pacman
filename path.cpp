#include "path.h"

Path::Path(QObject *parent) : QObject(parent)
{

}


Path::Path(QPoint startPoint, QGraphicsScene * scene,QVector<QVector<bool> >maze, QObject * parent) : QObject (parent), QGraphicsRectItem (){
    this->setRect(-PLAYER_EDGE / 2, -PLAYER_EDGE / 2,PLAYER_EDGE, PLAYER_EDGE);
    this->setPos(startPoint.x() * COORDINATE_SCALE, startPoint.y() * COORDINATE_SCALE);
    this->scene = scene;
    this->scene->addItem(this);
    this->maze = maze;
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

void Path::PathFinding(QPoint startPoint,QPoint target, int MaxStep){
    bool graph[MAZE_WIDTH + 1][MAZE_HEIGHT + 1];
    for(int i = 0; i < MAZE_WIDTH + 1; ++i){
        for(int j = 0; j < MAZE_HEIGHT + 1; ++j){
            graph[i][j] = maze[i][j];
        }
    }
    QVector<QPoint> movingVectors = {
        QPoint(1,0),
        QPoint(-1,0),
        QPoint(0,1),
        QPoint(0,-1)
    };

    QVector<QPointF> nodes;
    QVector<QPointF> forks;
    QVector<int> consecutiveSteps;
    int ableToGo = 0;
    QPointF p;
    nodes.push_back(this->pos());
    forks.push_back(this->pos());

    qDebug()<<nodes;

    QPointF temp;
    debugNode * dn;
    int step = -1;
    while (forks.size()) {
        // pop up
        p = nodes.last();

        p /= COORDINATE_SCALE;
        if(p == target){
            break;
        }
        graph[int(p.x())][int(p.y())] = true;
        dn = new debugNode(p.toPoint() * COORDINATE_SCALE);
        scene->addItem(dn);
        nodes.pop_back();
        for(int i = 0; i < movingVectors.size(); ++i){
            temp = p + movingVectors[i];
            if(!graph[int(temp.x())][int(temp.y())]){
                ++ableToGo;
//                qDebug()<<temp<<"this step can go forward";

                nodes.push_back(temp * 30);
            }
        }

        if(ableToGo > 1){ // means that p is fork
            // put in the fork
            forks.push_back(p);

            // record the consecutive step
            consecutiveSteps.push_back(step);

            //zeroing the step;
            step = -1;

        }else if(ableToGo == 1){
            ++step;
        }else{// means that meet the dead street;
            // pop the last forks;

        }
    }


}
