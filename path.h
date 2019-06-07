#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QPointF>
#include <QGraphicsScene>

class Path : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Path(QObject *parent = nullptr);
    explicit Path(QPoint startPoint, QGraphicsScene * scene, QObject *parent = nullptr);

signals:

public slots:
     QPoint giveMePath(QPoint startPos, QPoint targetPos);

private:
     QPoint judgeMovingVector(QPoint startPos, QPoint targetPos, int(QPoint::*coordinate)()const, void(QPoint::*setCoordinate)(int),QPoint & movingVector);
};

#endif // PATH_H
