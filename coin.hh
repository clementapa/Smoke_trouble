#ifndef COIN_HPP_
#define COIN_HPP_

#include "bonus.hh"
using namespace std;

class Coin: public Bonus{
  public:
    Coin(SDL_Renderer* ren):Bonus(0,0,80,80,"Img/Coin.png",ren,5,10){}
    ~Coin(){}
};

#endif
