#include "avatar.hh"

Avatar::Avatar(float x, float y, int h, int w, string filename, SDL_Renderer* ren, float vx, float vy, unsigned int l):Object_Dynamic(x,y,h,w,filename,ren,vx,vy),live(l){}

void Avatar::collision(const Object& o){

}

void Avatar::update(){

}
