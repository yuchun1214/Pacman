#include "dot.h"

Dot::Dot()
{

}

Dot::Dot(QPointF coordinate,QColor color) : QGraphicsRectItem()
{

    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
    this->setPos(coordinate);
    this->setRect(0 - DOT_SIZE / 2,0 - DOT_SIZE / 2,DOT_SIZE,DOT_SIZE);
}

PowerPellet::PowerPellet(){

}

PowerPellet::PowerPellet(QPointF coordinate){
    this->setPos(coordinate);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);
    this->setRect(0 - POWERPELLET_SIZE/ 2,0 - POWERPELLET_SIZE / 2,POWERPELLET_SIZE, POWERPELLET_SIZE);

//    this->setPos(coordinate);
}


DotManager::DotManager(QGraphicsScene * scene,QVector<QVector<bool> > maze,DashBoard * dashBoard,QObject * parent) : QObject (parent){
    this->scene = scene;
    this->maze = maze;
    connect(this,SIGNAL(eatDot()),dashBoard,SLOT(eatADot()));
}

void DotManager::deployTheDots(QPoint startPoint){
    bool graphArray[MAZE_WIDTH + 1][MAZE_HEIGHT + 1];

    for(int i = 0; i < MAZE_WIDTH + 1; ++i){
        QVector<Dot *> tempDots;
        for(int j = 0; j < MAZE_HEIGHT + 1; ++j){
            graphArray[i][j] = this->maze[i][j];
            tempDots.push_back(nullptr);
        }
        dots.push_back(tempDots);
    }

    QVector<QPoint> nodes;
    QVector<QPoint> movingVectors = {
        QPoint(1,0),
        QPoint(-1,0),
        QPoint(0,1),
        QPoint(0,-1)
    };

    QVector<QPoint> powerPelletCoordinate = {
        QPoint(25,1),
        QPoint(7,17),
        QPoint(21,15),
        QPoint(1,1)
    };

    QVector<QPoint> steps;
    QPoint temp;
    QPoint currentNode;
    Dot * dot;
    nodes.push_back(startPoint);
    int max = (MAZE_WIDTH + 1) * (MAZE_HEIGHT + 1);
    qDebug()<<"max = "<<max;
    int step = 0;
    while (nodes.size() && step < max) {
        // pop the last node
        currentNode = nodes.last();
        nodes.pop_back();
        if(!graphArray[currentNode.x()][currentNode.y()]){
            dot = new Dot(currentNode * COORDINATE_SCALE);
            dots[currentNode.x()][currentNode.y()] = dot;
            scene->addItem(dot);
            graphArray[currentNode.x()][currentNode.y()] = true;
            this->nodes.push_back(currentNode);
            ++step;
        }

        for(int i = 0, size = movingVectors.size(); i < size; ++i){
            temp = currentNode + movingVectors[i];
            if(!graphArray[temp.x()][temp.y()]){
//                qDebug()<<"this step is available "<<temp;
                nodes.push_back(temp);
            }
        }

    }

    for (int i = 0, size = powerPelletCoordinate.size(); i < size; ++i) {
        deleteTheDot(powerPelletCoordinate[i]);
        PowerPellet * p = new PowerPellet(powerPelletCoordinate[i] * COORDINATE_SCALE);
        dots[powerPelletCoordinate[i].x()][powerPelletCoordinate[i].y()] = p;
        scene->addItem(p);
    }
    qDebug()<<"step = "<<step;

}

void DotManager::eatenDot(QPoint dotPos){
//    qDebug()<<"slot eatenDot "<<dotPos;
    deleteTheDot(dotPos);
    emit eatDot();
}

void DotManager::deleteTheDot(QPoint p){
    delete dots[p.x()][p.y()];
    dots[p.x()][p.y()] = nullptr;
}

void DotManager::deleteTheDot(int x, int y){
    delete dots[x][y];
//    dots[x][y] = nullptr;
}

void DotManager::eatenPowerPellet(QPoint dotPos){
    qDebug()<<"slot powerPellet "<<dotPos;
    deleteTheDot(dotPos);
    emit eatPowerPellet();
}

QVector<QPointF> DotManager::Nodes(){
    return nodes;
}

QVector<QVector<Dot*> > DotManager::Dots(){
    return dots;
}
