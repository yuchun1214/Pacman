#include "dot.h"

Dot::Dot(QObject *parent) : QObject(parent)
{

}

Dot::Dot(QPointF coordinate,QColor color, QObject *parent) : QObject (parent), QGraphicsRectItem()
{
    QPen pen;
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
//    pen.setColor(Qt::gray);
//    this->setPen(pen);
    this->setBrush(brush);
    this->setPos(coordinate);
    this->setRect(0 - DOT_SIZE / 2,0 - DOT_SIZE / 2,DOT_SIZE,DOT_SIZE);
}
