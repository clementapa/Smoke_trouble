#ifndef OBJECT_DYNAMIC_HPP_
#define OBJECT_DYNAMIC_HPP_

#include "object.hh"

class Object_Dynamic: public Object{
  protected:
    float vx;
    float vy;

  public:
    Object_Dynamic(float x, float y, int h, int w, std::string filename, SDL_Renderer* ren, float vx, float vy):Object(x,y,h,w,filename,ren),vx(vx),vy(vy){}
    virtual ~Object_Dynamic(){}

    float getvx() const {return vx;}
    float getvy() const {return vy;}
    void setvx(float new_vx){vx=new_vx;}
    void setvy(float new_vy){vy=new_vy;}

    bool collision(Object* o);
    virtual void update(int w,int h) = 0;
};

#endif
