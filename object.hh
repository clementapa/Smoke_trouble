#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Object{
  protected:
    float x;
    float y;
    int h;
    int w;
    SDL_Texture* texture;

  public:
    Object(float x, float y, int h, int w, std::string filename, SDL_Renderer* ren);
    ~Object(){}

    void setObject(float x, float y, int w, int h);
    void setImage(std::string filename, SDL_Renderer* ren);

    float getx() const {return x;}
    float gety() const {return y;}
    int getw() const {return w;}
    int geth() const {return h;}
    void setx(float new_x){x=new_x;}
    void sety(float new_y){y=new_y;}
    void setw(float new_w){w=new_w;}
    void seth(float new_h){h=new_h;}
    SDL_Texture* getText() const {return texture;}

};

#endif
