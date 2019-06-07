#include "gameobject.h"


QPoint GameObject::tinyCoordinate(){
    return QPoint(int(this->x() / COORDINATE_SCALE), int(this->y() / COORDINATE_SCALE));
}
