#include "game.hh"
using namespace std;

Game::Game() {
  SDL_Init(0);
  SDL_CreateWindowAndRenderer(720, 480, 0, &win, &ren);//w=480(largeur) h=720 longueur
  SDL_SetWindowTitle(win, "Smoke trouble!!!");
  TTF_Init();
  running=true;
  count=0;
  wallpaper = new Object(0.0,0.0,480,720,"image.png",ren);
  avatar = new Avatar(300,405,80,80,"pompier.png",ren,10,10,5);
  vect_smoke.push_back(new Smoke(350,400,50,50,"pompier.png",ren,10,20,5));
  vect_smoke.push_back(new Smoke(10,50,50,50,"pompier.png",ren,10,20,5));
  font = TTF_OpenFont("Sans.ttf", 24);
  loop();
}

Game::~Game() {
  TTF_Quit();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

void Game::loop() {
  while(running) {

    lastFrame=SDL_GetTicks();
    static int lastTime;
    if(lastFrame >= (lastTime+1000)) {
      lastTime=lastFrame;
      frameCount=0;
    }

  //  cout << mousex << ", " << mousey << endl;
    render();
    input();
    update();
  }
}

void Game::update(){
    for(int i=0;i<2;i++)
      vect_smoke[i]->update(480,720);
}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      //if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
      if(e.key.keysym.sym == SDLK_q) {
        avatar->setx(avatar->getx()-avatar->getvx());
      }
      else if(e.key.keysym.sym == SDLK_d) {
        avatar->setx(avatar->getx()+avatar->getvy());
      }
    }
    if(e.type == SDL_KEYUP) {
      if(e.key.keysym.sym == SDLK_q) {}
    }
     SDL_GetMouseState(&mousex, &mousey);
  }
}

void Game::render() {

  draw(wallpaper);
  draw(avatar);
  draw("Score: 0", 20, 30, 0, 255, 0);
  draw(vect_smoke[0]);
  draw(vect_smoke[1]);

  frameCount++;
  int timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/60)) {
    SDL_Delay((1000/60)-timerFPS);
  }
  SDL_RenderPresent(ren);
}


void Game::draw(Object* o){
  SDL_Rect dstrect = { static_cast<Sint16>( o->getx()),static_cast<Sint16> (o->gety()),static_cast<Sint16> (o->getw()), static_cast<Sint16>(o->geth()) };
  SDL_RenderCopy(ren, o->getText(), NULL, &dstrect);
}

void Game::draw(const char* msg, int x, int y, int r, int g, int b) {
 SDL_Surface* surf;
 SDL_Texture* tex;
 SDL_Color color;
 color.r=r;
 color.g=g;
 color.b=b;
 color.a=255;
 SDL_Rect rect;
 surf = TTF_RenderText_Solid(font, msg, color);
 tex = SDL_CreateTextureFromSurface(ren, surf);
 rect.x=x;
 rect.y=y;
 rect.w=surf->w;
 rect.h=surf->h;
 SDL_FreeSurface(surf);
 SDL_RenderCopy(ren, tex, NULL, &rect);
 SDL_DestroyTexture(tex);
}
