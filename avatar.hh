#ifndef AVATAR_HPP_
#define AVATAR_HPP_

#include "object_dynamic.hh"
#include "game.hh"
using namespace std;

class Avatar: public Object_Dynamic{
  private:
    int live;

  public:
    Avatar(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, int l);
    ~Avatar(){}

    void collision(const Game& s);
    void update(const Game& s);
};

#endif
