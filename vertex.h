#ifndef VERTEX_H
#define VERTEX_H

#include "dot.h"
#include <QObject>
#include <QVector>
#include <QColor>
#include <QGraphicsScene>

class Vertex : public QObject
{
    Q_OBJECT
public:
    explicit Vertex(QObject *parent = nullptr);
    explicit Vertex(QGraphicsScene * scene,QColor color = Qt::gray, QObject * parent = nullptr);
private:
    QVector<Dot *> Dots;
    QGraphicsScene * scene;
    QColor color;

signals:

public slots:


public:
    int Cost();
    void hide();
    void setColor(QColor color);
    Dot * addDots(QPointF);

};

#endif // VERTEX_H
