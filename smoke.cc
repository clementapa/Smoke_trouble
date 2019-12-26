#include "smoke.hh"

Smoke::Smoke(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int s):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),size(s){}

void Smoke::collision(const Object& o){

}

void Smoke::update(){
  vy+=G*DT;
  x+=vx*DT;
  y+=vy*DT;
}
