#ifndef DEBUGNODE_H
#define DEBUGNODE_H

#include "def.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QBrush>

class debugNode :public QGraphicsRectItem{

private:
    QPoint _pos;
public:
    debugNode(qreal x, qreal y);
    debugNode(QPoint);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DEBUGNODE_H
