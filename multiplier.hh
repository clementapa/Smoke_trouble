#ifndef MULTIPLIER_HPP_
#define MULTIPLIER_HPP_

#include "bonus.hh"
using namespace std;

class Multiplier: public Bonus{
  public:
    Multiplier(SDL_Renderer* ren):Bonus(0,0,80,80,"Img/x2.png",ren,5,10){}
    ~Multiplier(){}
};

#endif
