#include "object_dynamic.hh"

bool Object_Dynamic::collision(Object* o){
  if( !( (o->getx() >= x + w) || (o->getx() + o->getw() <= x)  || (o->gety() >= y + h)  || (o->gety() + o->geth() <= y)) )
    return true;
  return false;
}
