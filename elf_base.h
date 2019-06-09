#ifndef ELF_BASE_H
#define ELF_BASE_H

#include "def.h"
#include <QObject>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QtMath>
#include "barrier.h"

class elf_base : public QGraphicsRectItem
{

public:
    explicit elf_base(QPoint position,QGraphicsScene * scene);
    QPointF moveTo(QPointF);
    virtual void move();

private:
   QGraphicsScene * scene;
   QPointF currentMovingVector;
   bool deadEnd;
   bool checkIfItHasBarrier(QPointF position);
};

class elf1 : public QObject, public elf_base
{
    Q_OBJECT

public:
    explicit elf1(QPoint startPos,QGraphicsScene * scene, QObject * paren = nullptr);
public:

    void test();
public slots:
    void move();
private:
    QGraphicsScene * scene;
    QTimer * timer;

};

#endif // ELF_BASE_H
