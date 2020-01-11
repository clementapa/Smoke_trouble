#include "object_dynamic.hh"

bool Object_Dynamic::collision(Object* o){
  if( !( (o->getx() >= x + w-5) || (o->getx() + o->getw() <= x+5)  || (o->gety() >= y + h)  || (o->gety() + o->geth() <= y+10 )) )
    return true;
  return false;
}
