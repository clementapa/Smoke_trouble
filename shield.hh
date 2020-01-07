#ifndef SHIELD_HPP_
#define SHIELD_HPP_

#include "bonus.hh"
using namespace std;

class Shield: public Bonus{
  public:
    Shield(SDL_Renderer* ren):Bonus(0,0,80,80,"Img/Shield.png",ren,5,10){}
    ~Shield(){}
};

#endif
