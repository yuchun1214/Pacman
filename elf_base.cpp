#include "elf_base.h"

elf_base::elf_base(QPoint position)
{
    this->setPos(position);
    this->setRect(- ELF_SIZE / 2,- ELF_SIZE / 2,ELF_SIZE,ELF_SIZE);
    QBrush br;
    br.setColor(Qt::blue);
    this->setBrush(br);
}

void elf_base::move(){

}


elf1::elf1(QPoint startPos,QGraphicsScene * scene,QObject * parent) : QObject (parent), elf_base(startPos){
    this->scene = scene;
}

void elf1::move(){


}
