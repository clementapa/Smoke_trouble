#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include "simu.hh"
//#define DT 0.01
//#define G 9.81

class Object{
  protected:
    float x;
    float y;
    float vx;
    float vy;

  public:
    Object(float x, float y, float vx, float vy):x(x),y(y),vx(vx),vy(vy){}
    virtual ~Object(){}

    virtual void draw(Simu s) const = 0;
    virtual void collision(const Simu& s) = 0;
    virtual void update(const Simu& s) = 0;
};

#endif
