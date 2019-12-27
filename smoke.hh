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
    Smoke(float x, float y, string filename, SDL_Renderer* ren, unsigned int s);    
    ~Smoke(){}

    void setsize(int new_s){size=new_s;}
    int getsize() const {return size;}
    void update(int w,int h);
};

#endif
