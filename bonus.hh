#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "object_dynamic.hh"
using namespace std;

class Bonus: public Object_Dynamic{
  protected:
    unsigned int time_effect;

  public:
    Bonus(float x, float y, int h, int w, string filename, SDL_Renderer* ren,float vy,unsigned int e);
    ~Bonus(){}

    void seteffect(int new_t){time_effect=new_t;}
    int geteffect() const {return time_effect;}
    void update(int w,int h);
    //virtual effect()
};

#endif
