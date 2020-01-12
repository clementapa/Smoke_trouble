#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "object_dynamic.hh"

class Bonus: public Object_Dynamic{
  public:
    Bonus(std::string filename, SDL_Renderer* ren);
    ~Bonus(){}

    void update(int w,int h);
    virtual std::string get_name()=0;
};

#endif
