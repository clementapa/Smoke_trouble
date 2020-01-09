#ifndef LIFE_HPP_
#define LIFE_HPP_

#include "bonus.hh"
using namespace std;

class Life: public Bonus{
  const string name ="Life";
  public:
    Life(SDL_Renderer* ren):Bonus("Img/Heart.png",ren){}
    ~Life(){}
     string get_name(){
       return name;
     }
};

#endif
