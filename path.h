#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QPointF>
#include <QVector>
#include <QGraphicsScene>
#include <map>
#include "debugnode.h"

class Path : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Path(QObject *parent = nullptr);
    explicit Path(QPoint startPoint, QGraphicsScene * scene,QVector<QVector<bool> >maze, QObject *parent = nullptr);

signals:

public slots:
     QPoint giveMePath(QPoint startPos, QPoint targetPos);
     void PathFinding(QPoint,QPoint,int MaxStep = 10000);

private:
     QVector<QVector< QPoint> > movingVectorsStack;
     QVector<QVector<bool> > maze;
     QGraphicsScene * scene;

private:
     QPoint judgeMovingVector(QPoint startPos, QPoint targetPos, int(QPoint::*coordinate)()const, void(QPoint::*setCoordinate)(int),QPoint & movingVector);

};

class TempPath{
private:
    QVector<QPointF> steps;
    QPointF startingPoint;
    QPointF lastStartingPoint;
    QVector<QPointF> children;
public:
    TempPath(QPointF start, QPointF last){
        steps.push_back(start);
        startingPoint = start;
        lastStartingPoint = last;
    }
    TempPath(){}

    void addStep(QPointF newPoint){
        steps.push_back(newPoint);
    }
    QPointF Start(){
        return startingPoint;
    }

    QPointF last(){
        return lastStartingPoint;
    }

    QVector<QPointF> Steps(){
        return steps;
    }

    QVector<QPointF> Children(){
        return children;
    }

    void addChild(QPointF child){
        children.push_back(child);
    }

};

#endif // PATH_H
