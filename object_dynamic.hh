#ifndef OBJECT_DYNAMIC_HPP_
#define OBJECT_DYNAMIC_HPP_

#include "object.hh"
#include "game.hh"
using namespace std;

class Object_Dynamic: public Object{
  protected:
    float vx;
    float vy;

  public:
    Object_Dynamic(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy):Object(x,y,h,w,filename,ren),vx(vx),vy(vy){}
    virtual ~Object_Dynamic(){}

    virtual void collision(const Game& s) = 0;
    virtual void update(const Game& s) = 0;
};

#endif
