#include "barrier.h"

Barrier::Barrier(QObject *parent) : QObject(parent), QGraphicsRectItem ()
{

}

Barrier::Barrier(QJsonObject config,bool mirror, QObject * parent) : QObject (parent), QGraphicsRectItem (){
    QJsonArray jspos = config["pos"].toArray();
    QPoint pos(jspos[0].toInt(), jspos[1].toInt());
    QJsonArray jsrect = config["rect"].toArray();
    QVector<int> vrect;
    QPoint rect;
    vrect.push_back(jsrect[0].toInt());
    vrect.push_back(jsrect[1].toInt());
    rect =  rectProcess(vrect[0],vrect[1]);
    this->setRect(pos.x() * COORDINATE_SCALE - errorneous_x, pos.y() * COORDINATE_SCALE - errorneous_y, rect.x(), rect.y());
    this->mid.setX(this->mid.x() + pos.x() * COORDINATE_SCALE);
    this->mid.setY(this->mid.y() + pos.y() * COORDINATE_SCALE);
    this->config = config;
}

QPoint Barrier::rectProcess(int &edge1, int &edge2){
    if(edge1 != edge2){
        if(edge1 != 0 && edge2 == 0){
            edge1 *= BARRIER_LONG;
            edge1 += BARRIER_SHORT;
            edge2 = BARRIER_SHORT;
            errorneous_x = (BARRIER_SHORT / 2);
//            errorneous_x = 0;
            errorneous_y = BARRIER_SHORT / 2;
            this->mid.setX(edge1 / 2);
            this->mid.setY(0);
        }else if(edge2 != 0 && edge1 == 0){
            edge2 *= BARRIER_LONG;
            edge2 += BARRIER_SHORT;
            edge1 = BARRIER_SHORT;
//            errorneous_y = 0;
            errorneous_x = BARRIER_SHORT / 2;
            errorneous_y = BARRIER_SHORT / 2;
            this->mid.setX(0);
            this->mid.setY(edge2 / 2);
        }
    }else{
        if(edge1 == edge2 && edge1 == 0){
            edge1 = edge2 = BARRIER_SHORT;
        }else{
            edge1 *= BARRIER_LONG;
            edge2 *= BARRIER_LONG;
        }
        errorneous_x = edge1 / 2;
        errorneous_y = edge2 / 2;
        this->mid.setX(0);
        this->mid.setY(0);
    }


    return  QPoint(edge1, edge2);
}

QJsonObject Barrier::Config(){
    return config;
}

QPoint Barrier::Mid(){
    return mid;
}

void Barrier::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<this->mid;
}
