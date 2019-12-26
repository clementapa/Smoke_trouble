#include "avatar.hh"

Avatar::Avatar(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, int l):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),live(l){}

void Avatar::collision(const Game& s){

}

void Avatar::update(const Game& s){
  
}
