#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;
#include "avatar.hh"
#include "smoke.hh"
#include "water.hh"

#define S_W 720
#define S_H 480

class Game {
public:
  Game();
  ~Game();
  void loop();
  void update();
  void input();
  void render();
  void init();
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
  Avatar* avatar;
  Water* water;
  bool end_game;
  int score;
  vector<Smoke*> vect_smoke;
  list<Smoke*> reserve_smoke;
};

#endif //GAME_H
