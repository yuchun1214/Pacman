#include "dot.h"

Dot::Dot(QObject *parent) : QObject(parent)
{

}

Dot::Dot(QPointF coordinate, QObject *parent) : QObject (parent), QGraphicsRectItem()
{
   this->setPos(coordinate);
   this->setRect(0 - DOT_SIZE / 2,0 - DOT_SIZE / 2,DOT_SIZE,DOT_SIZE);
}
