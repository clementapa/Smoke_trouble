#include "bonus.hh"

Bonus::Bonus(float x, float y, int h, int w, string filename, SDL_Renderer* ren,float vy, unsigned int e):Object_Dynamic(x,y,h,w,filename,ren,0,vy),time_effect(e){}

void Bonus::update(int s_w,int s_h){
  y+=vy;
  if (y+h>=s_w-45){
    y=s_w-h-45;
    vy=0;
  }
}
