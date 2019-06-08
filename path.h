#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QPointF>
#include <QVector>
#include <QGraphicsScene>
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

#endif // PATH_H
