#ifndef PLAYER_H
#define PLAYER_H

#include "def.h"
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QList>


#include "path.h"
#include "gameobject.h"
#include "barrier.h"
#include "dot.h"


namespace  PlayerParms{
    static QVector<QColor> DotColors = {
        Qt::gray,Qt::green,Qt::red, Qt::blue, Qt::black
    };
}

class Player :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    explicit Player(QPoint startPoint,QGraphicsScene * scene,DotManager * dm, QObject * parent = nullptr);

signals:
    void dotFinish();
    void eatADot(QPoint);
    void eatPowerPellet(QPoint);
public slots:

//    void deployDots();

    void move();


private:
    QGraphicsScene * scene;
    QVector<QPointF> backTrackStack;
    QPointF movingVectorPX;
    QPointF movingVectorNX;
    QPointF movingVectorPY;
    QPointF movingVectorNY;
    QTimer * timer;
    QPoint currentMovingVector;
    QPoint lastMovingVector;
//    QVector<Vertex *> vertices;
    QVector<QPointF> movingVectors;
    Path * path;
    int graphArray[MAZE_WIDTH + 1][MAZE_HEIGHT + 1];
//    Vertex * tempVertex;
    bool flag;

private:
    QPoint tinyCoordinate(QPoint);
    QPoint tinyCoordinate(QPointF);
    QPoint BigCoordinate(QPoint);





    // QGraphicsItem interface
protected:
    void keyPressEvent(QKeyEvent *event);



};

#endif // PLAYER_H
