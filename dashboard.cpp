#include "dashboard.h"

DashBoard::DashBoard(QObject *parent) : QGraphicsTextItem ()
{
    this->setPos(QPointF(810,0));
    this->setPlainText(QString("0"));
    score = 0;
    eatElfScore = 200;
}

void DashBoard::eatADot(){
    score += 10;
    this->setPlainText(QString::number(score));
}

void DashBoard::eatAnElf(){
    score += eatenElfs * 200;
    ++ eatenElfs;
    this->setPlainText(QString::number(score));
}


void DashBoard::becomeNormal(){
    eatenElfs = 1;
}
