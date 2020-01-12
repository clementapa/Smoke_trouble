#include "bonus.hh"
using namespace std;

Bonus::Bonus(string filename, SDL_Renderer* ren):Object_Dynamic(0,0,40,40,filename,ren,0,5){}

void Bonus::update(int s_w,int s_h){
  y+=vy;
  if (y+h>=s_w-(this->w)*1.5){
    y=s_w-h-(this->h)*1.5;
    vy=0;
  }
}
