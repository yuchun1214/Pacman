#ifndef DOT_H
#define DOT_H

#include "def.h"

#include <QObject>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QVector>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QSet>

#include "dashboard.h"

class Dot : public QGraphicsRectItem
{

public:
    explicit Dot();
    explicit Dot(QPointF coordinat,QColor color = Qt::gray);
signals:

public slots:

};

class PowerPellet : public Dot{

};

class DotManager : public QObject
{
    Q_OBJECT
public:
    explicit DotManager(QGraphicsScene * scene,QVector<QVector<bool> > maze,DashBoard * dashBoard,QObject * parent = nullptr);
    void deployTheDots(QPoint = QPoint(1,1));
    void deleteTheDot(QPoint p);
    void deleteTheDot(int x,int y);
    QVector<QVector<Dot*> >Dots();
signals:
    void eatDot();
public slots:
    void eatenDot(QPoint);
private:
    QGraphicsScene * scene;
    QVector<QVector<bool> > maze;
    QVector<QVector<Dot*> > dots;
private:
};

#endif // DOT_H
