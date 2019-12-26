#include "object.hh"

Object(float x, float y, int h, int w, string filename, SDL_Renderer* ren):x(x),y(y),h(h),w(w){
  SDL_Surface* surf = IMG_Load(filename.c_str());
  texture = SDL_CreateTextureFromSurface(ren, surf);
}

//Object(const Object& o):x(o.x),y(o.y),h(o.h),w(o.w){
//  SDL_Surface* surf = IMG_Load(filename.c_str());
//  texture = SDL_CreateTextureFromSurface(ren, surf);
//}

void Object::setObject(float x, float y, int w, int h){
  x=x;
  y=y;
  w=w;
  h=h;
}

void Object::setImage(string filename, SDL_Renderer* ren) {
  SDL_Surface* surf = IMG_Load(filename.c_str());
  tex = SDL_CreateTextureFromSurface(ren, surf);
}
