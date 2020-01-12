#ifndef COIN_HPP_
#define COIN_HPP_

#include "bonus.hh"

class Coin: public Bonus{
  const std::string name ="Coin";
  public:
    Coin(SDL_Renderer* ren):Bonus("Img/Coin.png",ren){}
    ~Coin(){}
    std::string get_name(){
      return name;
    }
};

#endif
