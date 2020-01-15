#ifndef LIFE_HPP_
#define LIFE_HPP_

#include "bonus.hh"

class Life: public Bonus{
  const std::string name ="Life";
  public:
    Life(SDL_Renderer* ren):Bonus("Img/Heart.png",ren){}
    ~Life(){}
     std::string get_name(){
       return name;
     }
};

#endif
