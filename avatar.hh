#ifndef AVATAR_HPP_
#define AVATAR_HPP_

#include "object_dynamic.hh"
using namespace std;

class Avatar: public Object_Dynamic{
  private:
    unsigned int live;

  public:
    Avatar(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int l);
    ~Avatar(){}

    void collision(const Object& o);
    void update(int w,int h);
};

#endif
