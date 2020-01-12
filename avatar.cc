#include "avatar.hh"
using namespace std;

Avatar::Avatar(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int l):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),live(l){}

void Avatar::update(int s_w,int s_h){
  if (x+w >= s_h)
    x=s_h-w;
  else if (x<=0)
      x=0;
}
