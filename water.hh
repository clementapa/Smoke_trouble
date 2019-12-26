#ifndef WATER_HPP_
#define WATER_HPP_

#include "object_dynamic.hh"
using namespace std;

class Water: public Object_Dynamic{
  public:
    Water(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy);
    ~Water(){}

    void collision(const Object& o);
    void update(int w,int h);
};

#endif
