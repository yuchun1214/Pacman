#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "def.h"

#include <QObject>
#include <QPoint>
#include <QPointF>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class GameObject : public QGraphicsItem
{
public:

    QPoint tinyCoordinate();

};

#endif // GAMEOBJECT_H
