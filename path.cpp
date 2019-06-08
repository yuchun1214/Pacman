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


//    std::map<QPointF, TempPath> partitionStep;
    QVector<TempPath> partitionStep;
    QVector<TempPath> tempPartitionStep;
    QPointF tempNode;
    QVector<QPointF> tempSteps;
    QPointF p = startPoint;
    int currentStep = 0;
    QVector<QPointF> nodes;

    partitionStep.push_back(TempPath(p,p));


    nodes.push_back(this->pos() / COORDINATE_SCALE );
    while(currentStep < MaxStep){
        // go a step;

        for(int i = 0; i < partitionStep.size(); ++i){
            p = partitionStep[i].Steps().last();

            if(p == target){
                qDebug()<<"find the path";
                return;
            }
            for(int i = 0; i < movingVectors.size(); ++i){
                tempNode = movingVectors[i] + p;
                if(!graph[int(tempNode.x())][int(tempNode.y())]){
                     nodes.push_back(tempNode);
                }
            }

            if(nodes.size() > 1){
                // add the forks
                for (int i = 0; i < nodes.size(); ++i) {
                    tempPartitionStep.push_back(TempPath(nodes[i],p));
                }
                nodes.clear();
            }/*else if(!nodes.size()){ // meet the dead street

                partitionStep.erase(it);

            }*/else if(nodes.size() == 1){ // only one node could go forward
               partitionStep[i].addStep(nodes[0]);
            }
        }
        for (int i = 0; i < tempPartitionStep.size(); ++i) {
            partitionStep.push_back(tempPartitionStep[i]);
        }

        tempPartitionStep.clear();
        ++ currentStep;
        qDebug()<<"current step "<<currentStep;
    }
}
