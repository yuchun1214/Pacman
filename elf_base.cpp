#include "elf_base.h"


elf_base::elf_base(QPoint position,QGraphicsScene * scene)
{
    this->setPos(position);
    this->setRect(- ELF_SIZE / 2,- ELF_SIZE / 2,ELF_SIZE,ELF_SIZE);
    QBrush br;
    br.setColor(Qt::blue);
    this->setBrush(br);
    this->scene = scene;
    deadEnd = false;
}

void elf_base::move(){
//    this->setPos(this->pos() + this->moveTo(target) * COORDINATE_SCALE);
}

void elf_base::beGhost(){
    qDebug()<<"be ghost";
}

QPointF elf_base::moveTo(QPointF target){
//    target = target / COORDINATE_SCALE;
    QPointF pathVector = target - this->pos();
    if(pathVector == QPointF(0,0)){
        currentMovingVector = QPointF(0,0);
        return currentMovingVector;
    }

    if(int(pathVector.x()) != 0){
        pathVector.setX(pathVector.x() / qFabs(pathVector.x()));
    }
    if(int(pathVector.y()) != 0){
        pathVector.setY(pathVector.y() / qFabs(pathVector.y()));
    }


    qDebug()<<"\n\npath vector"<<pathVector;
    // horizontal
    bool horizontalCouldGoForward = checkIfItHasBarrier(QPointF(this->pos().x() + pathVector.x() * COORDINATE_SCALE, this->pos().y()));

//    QList<QGraphicsItem*> hitems = this->scene->items(QPointF(this->pos().x() + pathVector.x() * COORDINATE_SCALE, this->pos().y()));
//    for(int i = 0, size = hitems.size(); i < size; ++i){
//        if(typeid(*(hitems[i])) == typeid (Barrier)){
//            horizontalCouldGoForward = false;
//            break;
//        }
//    }
    if(int(pathVector.x()) == 0){
        horizontalCouldGoForward = false;
    }

    // vertical
    bool verticalCouldGoForward = checkIfItHasBarrier(QPointF(this->pos().x(), this->pos().y() + pathVector.y() * COORDINATE_SCALE));
//    QList<QGraphicsItem*> vitems = this->scene->items(QPointF(this->pos().x(), this->pos().y() + pathVector.y() * COORDINATE_SCALE));
//    for(int i = 0, size = vitems.size(); i < size; ++i){
//        if(typeid(*(vitems[i])) == typeid (Barrier)){
//            verticalCouldGoForward = false;
//            break;
//        }
//    }
    if(int(pathVector.y()) == 0){
        verticalCouldGoForward = false;
    }
    qDebug()<<"horizontal = "<<horizontalCouldGoForward<<"\nvertical = "<<verticalCouldGoForward<<"\ndeadend = "<<deadEnd;


    if(!deadEnd){
        qDebug()<<"66";
        if(horizontalCouldGoForward && !verticalCouldGoForward || (horizontalCouldGoForward && verticalCouldGoForward)){
            currentMovingVector = QPointF(pathVector.x(),0);
            deadEnd = false;
        }else if(!horizontalCouldGoForward && verticalCouldGoForward){
            currentMovingVector = QPointF(0,pathVector.y());
            deadEnd = false;
        }else if(!horizontalCouldGoForward && !verticalCouldGoForward){ // means that meet the dead end;
            qDebug()<<"dead end";
            deadEnd = true;
            if(int(currentMovingVector.x())){ // means that current movingVector is horizontal I need to find a vertical way to escape dead end
                if(!int(pathVector.y())){
                    // if current pos and the target are in horizontal
                    // I need to check if up can go or down
                    bool up = checkIfItHasBarrier(QPointF(this->pos().x(),this->pos().y() - COORDINATE_SCALE));
                    bool down = checkIfItHasBarrier(QPointF(this->pos().x(),this->pos().y() + COORDINATE_SCALE));
                    qDebug()<<"up = "<<up<<"\ndown = "<<down;
                    if(up){
                        currentMovingVector.setY(-1);
                        currentMovingVector.setX(0);
                    }else if(down){
                        qDebug()<<"84";
                        currentMovingVector.setY(1);
                        currentMovingVector.setX(0);
                    }
                    else{
                        qDebug()<<"91";
                        currentMovingVector *= (-1);
                    }

                }
                else currentMovingVector *= -1;
//                    currentMovingVector = QPointF(0, pathVector.y() * ( -1 ));

            }else if(int(currentMovingVector.y())){ // means that current movingVector is vertical I need to find a horizontal way to escape dead end
                if(!int(pathVector.x())){
                    bool left = checkIfItHasBarrier(QPointF(this->pos().x() - COORDINATE_SCALE, this->pos().y()));
                    bool right = checkIfItHasBarrier(QPointF(this->pos().x() + COORDINATE_SCALE, this->pos().y()));
                    if(left){
                        currentMovingVector.setX(-1);
                        currentMovingVector.setY(0);
                    }else if(right){
                        currentMovingVector.setX(1);
                        currentMovingVector.setY(0);
                    }else{
                        currentMovingVector *= -1;
                    }

                }
                else currentMovingVector *= -1;
//                    currentMovingVector = QPointF(pathVector.x() * ( - 1), 0);
            }
        }
    }else{
        // if now is dead and find a correct way to escape dead end, relieve dead end flag
        if(int(currentMovingVector.x()) && verticalCouldGoForward){
            deadEnd = false; // remove dead end flag
            currentMovingVector.setX(0);
            currentMovingVector.setY(pathVector.y());
        }else if(int(currentMovingVector.y()) && horizontalCouldGoForward){
            deadEnd = false;
            currentMovingVector.setX(pathVector.x());
            currentMovingVector.setY(0);
        }
    }
    return currentMovingVector;
}

bool elf_base::checkIfItHasBarrier(QPointF position){
    QList<QGraphicsItem*> items = this->scene->items(position);
    for(int i = 0, size = items.size(); i < size; ++i){
        if(typeid(*(items[i])) == typeid (Barrier)){
            return  false;
        }
    }
    return true;
}

elf1::elf1(QPoint startPos,QGraphicsScene * scene,Player * player,QObject * parent) : QObject (parent), elf_base(startPos,scene){

    this->scene = scene;
    timer = new QTimer();
    timer->start(100);
    this->player = player;
    QBrush br;
    br.setStyle(Qt::SolidPattern);
    br.setColor(Qt::red);
    this->setBrush(br);
//    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void elf1::move(){
    QPointF movingVector = elf_base::moveTo(player->pos())* COORDINATE_SCALE;
    setPos(this->pos() + movingVector);
}

void elf1::test(){
    QPointF t;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}


elf2::elf2(QPoint startPos,QGraphicsScene * scene,Player * player,QObject * parent) : QObject (parent), elf_base(startPos,scene){
    this->scene = scene;
    timer = new QTimer();
    timer->start(100);
    this->player = player;
}

void elf2::move(){
    qDebug()<<"move";
    QPointF movingVector = elf_base::moveTo(player->pos())* COORDINATE_SCALE;
    qDebug()<<"movingVector = "<<movingVector;
    setPos(this->pos() + movingVector);
}

elf3::elf3(QPoint startPos,QGraphicsScene * scene,Player * player,QObject * parent) : QObject (parent), elf_base(startPos,scene){
    this->scene = scene;
    timer = new QTimer();
    timer->start(100);
    this->player = player;
}

void elf3::move(){
    qDebug()<<"move";
    QPointF movingVector = elf_base::moveTo(player->pos())* COORDINATE_SCALE;
    qDebug()<<"movingVector = "<<movingVector;
    setPos(this->pos() + movingVector);
}

elf4::elf4(QPoint startPos,QGraphicsScene * scene,Player * player,QObject * parent) : QObject (parent), elf_base(startPos,scene){
    this->scene = scene;
    timer = new QTimer();
    timer->start(100);
    this->player = player;
}

void elf4::move(){
    qDebug()<<"move";
    QPointF movingVector = elf_base::moveTo(player->pos())* COORDINATE_SCALE;
    qDebug()<<"movingVector = "<<movingVector;
    setPos(this->pos() + movingVector);
}
