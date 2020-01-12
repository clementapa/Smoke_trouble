#ifndef MULTIPLIER_HPP_
#define MULTIPLIER_HPP_

#include "bonus.hh"

class Multiplier: public Bonus{
  const std::string name ="Multiplier";
  public:
    Multiplier(SDL_Renderer* ren):Bonus("Img/x2.png",ren){}
    ~Multiplier(){}
    std::string get_name(){
      return name;
    }
};

#endif
