#ifndef BARRIER_H
#define BARRIER_H

#include "def.h"

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QDebug>
#include <QString>
#include <QBrush>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

class Barrier : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Barrier(QObject *parent = nullptr);
    explicit Barrier(QJsonObject config, bool mirror = true, QObject * parent = nullptr);

    QPoint Mid();
    QJsonObject Config();

signals:

public slots:

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:

    int width;
    int height;
    QPoint mid;
    int errorneous_x;
    int errorneous_y;
    QJsonObject config;
    QPoint rectProcess(int & longedge, int & shortedge);

};

#endif // BARRIER_H
