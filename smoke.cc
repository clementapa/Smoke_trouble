#include "smoke.hh"

Smoke::Smoke(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int s):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),size(s){}

void Smoke::collision(const Object& o){

}

void Smoke::update(int s_w, int s_h){
  if(y-h/2<=0.0 || y+h/2>=s_w){//sol et haut
    vx*=0.95;
    vy*=-0.85;
    if(y-h/2<=0.0)
      y=h/2;
    else
      y=s_w-h/2;
  }
  else if(x-w/2<=0.0|| x+w/2>=s_h){
    vx*=-0.85;
    vy*=0.95;
    if(x-w/2<=0.0)
      x=w/2;
    else
      x=s_h-w/2;
  }
  x+=vx*DT;
  y+=vy*DT;
}
