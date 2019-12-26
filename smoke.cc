#include "smoke.hh"

Smoke::Smoke(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int s):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),size(s){}

void Smoke::collision(const Object& o){

}

void Smoke::update(int s_w, int s_h){
  if(y<=0.0 || y+h>=s_w){//sol et haut
    vx*=0.95;
    vy*=-0.85;
    if(y<=0.0)
      y=0;
    else
      y=s_w-h;
  }
  else if(x<=0.0|| x+w>=s_h){
    vx*=-0.85;
    vy*=0.95;
    if(x<=0.0)
      x=0;
    else
      x=s_h-w;
  }
  x+=vx*DT;
  y+=vy*DT;
}
