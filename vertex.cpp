#include "vertex.h"

Vertex::Vertex(QObject *parent) : QObject(parent)
{

}

Vertex::Vertex(QGraphicsScene * scene,QColor color, QObject * parent) : QObject (parent){
    this->scene = scene;
    this->color = color;
}

int Vertex::Cost(){
    return  Dots.size();
}

void Vertex::setColor(QColor color){
    this->color = color;
}

void Vertex::hide(){
    for(int i = 0, size = Dots.size(); i < size; ++i){
        Dots[i]->hide();
    }
}

Dot * Vertex::addDots(QPointF dotPos){
    Dot * dot = new Dot(dotPos,this->color);
    this->scene->addItem(dot);
    Dots.push_back(dot);
    return dot;
}
