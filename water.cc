#include "water.hh"

Water::Water(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy):Object_Dynamic(x,y,h,w,filename,ren,vx,vy){}

void Water::update(int s_w, int s_h){
  x+=vx;
  y+=vy;
}
