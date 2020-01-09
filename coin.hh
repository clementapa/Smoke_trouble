#ifndef COIN_HPP_
#define COIN_HPP_

#include "bonus.hh"
using namespace std;

class Coin: public Bonus{
  const string name ="Coin";
  public:
    Coin(SDL_Renderer* ren):Bonus("Img/Coin.png",ren){}
    ~Coin(){}
    string get_name(){
      return name;
    }
};

#endif
