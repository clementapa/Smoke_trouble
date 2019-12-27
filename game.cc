#include "game.hh"
using namespace std;

Game::Game() {
  SDL_Init(0);
  SDL_CreateWindowAndRenderer(S_W, S_H, 0, &win, &ren);//w=480(largeur) h=720 longueur
  SDL_SetWindowTitle(win, "Smoke trouble!!!");
  TTF_Init();
  running=true;
  count=0;
  wallpaper = new Object(0.0,0.0,S_H,S_W,"Img/image.png",ren);
  avatar = new Avatar(S_W/2-40,S_H-80,80,80,"Img/pompier.png",ren,10,10,5);
  water = new Water(S_W*10,-S_H*10,80,80,"Img/water.png",ren,0,0);
  vect_smoke.push_back(new Smoke(S_W-100,130,100,100,"Img/fire.png",ren,-20,-20,3));
  vect_smoke.push_back(new Smoke(0,130,100,100,"Img/fire.png",ren,20,-20,3));
  font = TTF_OpenFont("font/Sans.ttf", 24);
  end_game=false;
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
  for(size_t i=0;i<vect_smoke.size();i++){
    vect_smoke[i]->update(S_H,S_W);
    if(avatar->collision(vect_smoke[i])){
      avatar->setlive(avatar->getlive()-1);
      if(avatar->getlive()==0)
              end_game=true;
    }
    else if(water->collision(vect_smoke[i])){
      if((vect_smoke[i]->getsize())-1!=0){
        vect_smoke.push_back(new Smoke(vect_smoke[i]->getx(),vect_smoke[i]->gety(),(vect_smoke[i]->geth())/2,(vect_smoke[i]->getw())/2,"Img/fire.png",ren,-vect_smoke[i]->getvx(),vect_smoke[i]->getvy(),vect_smoke[i]->getsize()-1));
        vect_smoke[i]->seth((vect_smoke[i]->geth())/2);
        vect_smoke[i]->setw((vect_smoke[i]->getw())/2);
        vect_smoke[i]->setsize((vect_smoke[i]->getsize())-1);
      }
      else
        vect_smoke.erase(vect_smoke.begin()+i);
      water->setx(S_W*10);
      water->sety(-S_H*10);
    }
  avatar->update(S_H,S_W);
  water->update(S_H,S_W);
  }
}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
      if(e.key.keysym.sym == SDLK_SPACE && end_game==false){
        if(water->gety()<0){
          water->setx(avatar->getx() + avatar->getw()/2 - water->getw()/2);
          water->sety(avatar->gety());
          water->setvx(0.0);
          water->setvy(-10.0);

        }
      }
      if(e.key.keysym.sym == SDLK_q && end_game==false) {
        avatar->setx(avatar->getx()-avatar->getvx());
      }
      else if(e.key.keysym.sym == SDLK_d && end_game==false) {
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
  for(size_t i=0;i<vect_smoke.size();i++){
    draw(vect_smoke[i]);
  }
  draw(water);

  if(avatar->getlive()==0){
    draw("GAME OVER", S_H/2, S_W/2, 0, 255, 0);
  }

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
