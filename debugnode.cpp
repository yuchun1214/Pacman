#include "debugnode.h"


debugNode::debugNode(qreal x, qreal y){
    QBrush br(Qt::red);
    this->_pos = QPoint(x,y);
    this->setPos(QPointF(x - DEBUGNODE_SIZE / 2, y - DEBUGNODE_SIZE / 2));
    this->setRect(0,0,DEBUGNODE_SIZE,DEBUGNODE_SIZE);
    this->setBrush(br);
}

debugNode::debugNode(QPoint pos){
    QBrush br(Qt::red);
    this->setPos(pos);
    this->setRect(-DEBUGNODE_SIZE / 2, -DEBUGNODE_SIZE / 2,DEBUGNODE_SIZE, DEBUGNODE_SIZE);
    this->setBrush(br);
}

void debugNode::mousePressEvent(QGraphicsSceneMouseEvent *event){

    qDebug()<<this->_pos;
//    qDebug()<<QPoint((this->rect().x() + DEBUGNODE_SIZE / 2), (this->rect().y() + DEBUGNODE_SIZE / 2));
}
