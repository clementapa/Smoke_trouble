#ifndef MULTIPLIER_HPP_
#define MULTIPLIER_HPP_

#include "bonus.hh"
using namespace std;

class Multiplier: public Bonus{
  const string name ="Multiplier";
  public:
    Multiplier(SDL_Renderer* ren):Bonus("Img/x2.png",ren){}
    ~Multiplier(){}
    string get_name(){
      return name;
    }
};

#endif
