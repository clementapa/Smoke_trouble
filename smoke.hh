#ifndef SMOKE_HPP_
#define SMOKE_HPP_

#define DT 0.1
#define G 9.81

#include "object_dynamic.hh"
using namespace std;

class Smoke: public Object_Dynamic{
  private:
    unsigned int size;

  public:
    Smoke(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int s);
    ~Smoke(){}

    void collision(Object* o);
    void update(int w,int h);
};

#endif
