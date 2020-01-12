#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "avatar.hh"
#include "smoke.hh"
#include "water.hh"
#include "bonus.hh"
#include "coin.hh"
#include "life.hh"
#include "multiplier.hh"


#define S_W 1366
#define S_H 768
#define G_H 63
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
  int frameCount, timerFPS, lastFrame;
  Object* wallpaper;
  Object* Heart;
  Object* Ground;
  Object* GameOver;
  //Object* Loading;

  //Object* Congrats;
  int mousex, mousey;
  Avatar* avatar;
  Water* water;
  Water* SMoke;

  bool end_game;
  bool stop;
  int score;
  int round;
  int multiplier;
  int time;
  vector<Smoke*> vect_smoke;
  list<Smoke*> reserve_smoke;
  vector<Bonus*> reserve_bonus;
  vector<Bonus*> vect_bonus;
};

#endif //GAME_H
