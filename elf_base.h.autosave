#ifndef ELF_BASE_H
#define ELF_BASE_H

#include "def.h"
#include <QObject>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QtMath>
#include <QVector>
#include "barrier.h"
#include "player.h"


class elf_base : public QGraphicsRectItem
{

public:
    explicit elf_base(QPoint position,QGraphicsScene * scene,QVector<QPointF> nodes);
    QPointF moveTo(QPointF);
    virtual void move();
    virtual void isGhostMove();
    virtual void beGhost();
private:
   QGraphicsScene * scene;
   QPointF currentMovingVector;
   QVector<QPointF> nodes;
   bool deadEnd;
   bool checkIfItHasBarrier(QPointF position);
};

class elf1 : public QObject, public elf_base
{
    Q_OBJECT

public:
    explicit elf1(QPoint startPos,QGraphicsScene * scene,Player * player,QVector<QPointF> nodes, QObject * paren = nullptr);
public:

    void test();
public slots:
    void move();
private:
    QGraphicsScene * scene;
    QTimer * timer;
    Player * player;
};

class elf2 : public QObject, public elf_base{
    Q_OBJECT
public:
    explicit elf2(QPoint startPos, QGraphicsScene * scene, Player * player,QVector<QPointF> nodes, QObject * parent = nullptr);

public slots:
    void move();
private:
    QGraphicsScene * scene;
    QTimer * timer;
    Player * player;

};

class elf3 : public QObject, public elf_base{
    Q_OBJECT
public:
    explicit elf3(QPoint startPos, QGraphicsScene * scene, Player * player,QVector<QPointF> nodes, QObject * parent = nullptr);

public slots:
    void move();

private:
    QGraphicsScene * scene;
    QTimer * timer;
    Player * player;

};

class elf4 : public QObject, public elf_base{
    Q_OBJECT
public:
    explicit elf4(QPoint startPos, QGraphicsScene * scene, Player * player,QVector<QPointF> nodes, QObject * parent = nullptr);

public slots:
    void move();

private:
    QGraphicsScene * scene;
    QTimer * timer;
    Player * player;

};


#endif // ELF_BASE_H
