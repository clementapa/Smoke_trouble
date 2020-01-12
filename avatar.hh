#ifndef AVATAR_HPP_
#define AVATAR_HPP_

#include "object_dynamic.hh"

class Avatar: public Object_Dynamic{
  private:
    unsigned int live;

  public:
    Avatar(float x, float y, int h, int w, std::string filename, SDL_Renderer* ren, float vx, float vy, unsigned int l);
    ~Avatar(){}

    void setlive(int new_l){live=new_l;}
    int getlive() const {return live;}
    void update(int w,int h);
};

#endif
