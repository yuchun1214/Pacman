#ifndef PLAYER_H
#define PLAYER_H

#include "def.h"
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "dot.h"
#include "vertex.h"

namespace  PlayerParms{
    static QVector<QColor> DotColors = {
        Qt::gray,Qt::green,Qt::red, Qt::blue, Qt::black
    };
}

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    explicit Player(QPoint startPoint,QGraphicsScene * scene, QObject * parent = nullptr);
    QVector<Vertex *> Vertices();
signals:
    void dotFinish();
public slots:

    void move();


private:
    QGraphicsScene * scene;
    QVector<QPointF> backTrackStack;
    QPointF movingVectorPX;
    QPointF movingVectorNX;
    QPointF movingVectorPY;
    QPointF movingVectorNY;
    QTimer * timer;
    QVector<Vertex *> vertices;
    QVector<QPointF> movingVectors;
    int graphArray[MAZE_WIDTH + 1][MAZE_HEIGHT + 1];
    Vertex * tempVertex;
    bool flag;

private:
    void showGraphArray();


};

#endif // PLAYER_H
