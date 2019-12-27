#include "smoke.hh"

Smoke::Smoke(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int s):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),size(s){}

Smoke::Smoke(float x, float y, string filename, SDL_Renderer* ren, unsigned int s):Object_Dynamic(x,y,100,100,filename,ren,0,0),size(s){
  if (s == 2){
    h=h/2;
    w=w/2;
  }
  else if( s==1 ){
    h=h/4;
    w=w/4;
  }
}

void Smoke::update(int s_w, int s_h){

  vy=vy + 100*0.01;
  x+=vx*DT;
  y+=vy*DT;

  if(y<=0.0 || y+h>=s_h){//sol et haut
    vx*=1;
    vy*=-0.85;
    if(y<=0.0)
      y=0;
    else{
      y=s_h-h ;
      vy=-80;
    }
  }
  else if(x<=0.0|| x+w>=s_w){
    vx*=-1;
    vy*=0.95;
    if(x<=0.0)
      x=0;
    else
      x=s_w-w;
    }

}
