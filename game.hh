#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;
#include "object.hh"
//#include "avatar.hh"

class Game {
public:
  Game();
  ~Game();
  void loop();
  void update(){}
  void input();
  void render();
  void draw(Object* o);
  void draw(const char* msg, int x, int y, int r, int g, int b);
private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int count;
  int frameCount, timerFPS, lastFrame;
  Object* wallpaper;
  int mousex, mousey;
  //Avatar* avatar;
};

#endif //GAME_H
