#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;
//#define DT 0.01
//#define G 9.81

class Object{
  protected:
    float x;
    float y;
    int h;
    int w;
    SDL_Texture* texture;

  public:
    Object(float x, float y, int h, int w, string filename, SDL_Renderer* ren);
    //Object(const Object& o);

    ~Object(){}

    void setObject(float x, float y, int w, int h);
    void setImage(string filename, SDL_Renderer* ren);

    float getx() const {return x;}
    float gety() const {return y;}
    int getw() const {return w;}
    int geth() const {return h;}
    SDL_Texture* getText() const {return texture;}

};

#endif
