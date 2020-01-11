#include "object_dynamic.hh"

bool Object_Dynamic::collision(Object* o){
  if( !( (o->getx() >= x + w-16) || (o->getx() + o->getw() <= x+16)  || (o->gety() >= y + h)  || (o->gety() + o->geth() <= y+15 )) )
    return true;
  return false;
}
