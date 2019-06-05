#ifndef DOT_H
#define DOT_H

#include "def.h"

#include <QObject>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>

class Dot : public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Dot(QObject *parent = nullptr);
    explicit Dot(QPointF coordinat,QColor color = Qt::gray, QObject * parent = nullptr);
signals:

public slots:
};

#endif // DOT_H
