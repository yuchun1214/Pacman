#ifndef ELF_BASE_H
#define ELF_BASE_H

#include "def.h"
#include <QObject>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class elf_base : public QGraphicsRectItem
{

public:
    explicit elf_base(QPoint position);
    virtual void move();
};

class elf1 : public QObject, public elf_base
{
    Q_OBJECT

public:
    explicit elf1(QPoint startPos,QGraphicsScene * scene, QObject * paren = nullptr);
public:
    void move();
private:
    QGraphicsScene * scene;

};

#endif // ELF_BASE_H
