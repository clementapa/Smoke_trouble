#include <string>
#include "game.hh"
using namespace std;


Game::Game() {
  SDL_Init(0);
  SDL_CreateWindowAndRenderer(S_W, S_H, 0, &win, &ren);//w=480(largeur) h=720 longueur
  SDL_SetWindowTitle(win, "Fire trouble!!!");
  TTF_Init();
  running=true;
  round=1;

  wallpaper = new Object(0.0,0.0,S_H,S_W,"Img/wallpaper4.jpg",ren);
  Ground=new Object(0,S_H-67,67,S_W,"Img/sol.jpg",ren);
  Heart=new Object(10,10,30,30,"Img/Heart2.png",ren);
  //Congrats=new Object(S_W/2-250,S_H/2-300,400,500,"Img/Congrats.png",ren);
  GameOver=new Object(S_W/2-250,S_H/2-300,400,500,"Img/GameOver2.png",ren);

  avatar = new Avatar(S_W/2-40,S_H-G_H-123,123,66,"Img/pompier.png",ren,15,10,5);

  water = new Water(S_W*10,-S_H*10,600,10,"Img/water_line.png",ren,0,0);

  vect_smoke.push_back(new Smoke(S_W-100,100,100,100,"Img/fire.png",ren,-20,-20,3));
  vect_smoke.push_back(new Smoke(0,100,100,100,"Img/fire.png",ren,20,-20,3));

  for(int i=0;i<6;i++)
    reserve_smoke.push_back(new Smoke(0,0,0,0,"Img/fire.png",ren,0,0,3));

  font = TTF_OpenFont("font/Sans3.ttf", 24);
  end_game=false;
  score=0;
    loop();
}


void Game::init(){

  std::cout << "init" << '\n';
/*Je vide mon vect smoke en mettant les balles dans la reserve*/
  size_t size=vect_smoke.size();
  for(size_t i=0;i<size;i++){
    reserve_smoke.push_back(vect_smoke[i]);
    std::cout << "for" << '\n';
  }
      vect_smoke.clear();
  /*je remets l avatar au milieu du jeu*/
  avatar->setx(S_W/2-40);

/*je prend les deux premieres balles de la reserve et je les transforment en grandes balles*/
/*puis je les push dans vect smoke*/
  reserve_smoke.front()->setx(S_W-100);
  reserve_smoke.front()->sety(100);
  reserve_smoke.front()->seth(100);
  reserve_smoke.front()->setw(100);
  reserve_smoke.front()->setvx(-20 -round*14);
  reserve_smoke.front()->setvy(-20);
  reserve_smoke.front()->setsize(3);

  vect_smoke.push_back(reserve_smoke.front());
  reserve_smoke.erase(reserve_smoke.begin());

  reserve_smoke.front()->setx(0);
  reserve_smoke.front()->sety(100);
  reserve_smoke.front()->seth(100);
  reserve_smoke.front()->setw(100);
  reserve_smoke.front()->setvx(20+round*10);
  reserve_smoke.front()->setvy(-20);
  reserve_smoke.front()->setsize(3);

  vect_smoke.push_back(reserve_smoke.front());
  reserve_smoke.erase(reserve_smoke.begin());

  /*vect_smoke.push_back(new Smoke(S_W-100,130,100,100,"Img/fire.png",ren,-20,-20,3));
  vect_smoke.push_back(new Smoke(0,130,100,100,"Img/fire.png",ren,20,-20,3));
*/
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
    input();
    render();
    update();
  }
}

void Game::update(){

  for(size_t i=0;i<vect_smoke.size();i++){
    vect_smoke[i]->update(S_W,S_H-G_H);
  if(avatar->collision(vect_smoke[i])){
    avatar->setlive(avatar->getlive()-1);
    init();
  }
  else if(water->collision(vect_smoke[i])){
      if((vect_smoke[i]->getsize())-1!=0){

        reserve_smoke.front()->setx(vect_smoke[i]->getx());
        reserve_smoke.front()->sety(vect_smoke[i]->gety()-50);
        reserve_smoke.front()->seth(vect_smoke[i]->geth()/2);
        reserve_smoke.front()->setw(vect_smoke[i]->getw()/2);
        reserve_smoke.front()->setvx(-vect_smoke[i]->getvx());
        reserve_smoke.front()->setvy(-10);
        reserve_smoke.front()->setsize(vect_smoke[i]->getsize()-1);
        vect_smoke.push_back(reserve_smoke.front());

        reserve_smoke.erase(reserve_smoke.begin());

        vect_smoke[i]->seth((vect_smoke[i]->geth())/2);
        vect_smoke[i]->setw((vect_smoke[i]->getw())/2);
        vect_smoke[i]->sety(vect_smoke[i]->gety()-50);
        vect_smoke[i]->setvy(-10);
        vect_smoke[i]->setsize((vect_smoke[i]->getsize())-1);
      }
      else{
        reserve_smoke.push_back(vect_smoke[i]);
        vect_smoke.erase(vect_smoke.begin()+i);

      }
      if (vect_smoke.empty()) {
        init();
        round++;
      }
      score+=500;
      water->setx(S_W*10);
      water->sety(-S_H*10);
    }
  }
  avatar->update(S_H,S_W);
  water->update(S_H,S_W);
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
          water->sety(avatar->gety()-G_H);
          water->setvy(-10.0);
        }
      }
      if(e.key.keysym.sym == SDLK_q && end_game==false) {
        avatar->setx(avatar->getx()-avatar->getvx());
      }
      else if(e.key.keysym.sym == SDLK_d && end_game==false) {
        avatar->setx(avatar->getx()+avatar->getvy());
      }
      else if(e.key.keysym.sym == SDLK_r && avatar->getlive()==0) {
        avatar->setlive(5);
        score=0;
        init();
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
  draw(water);
  draw(Ground);
  for (int i = 0; i < avatar->getlive(); i++) {
    draw(Heart);
    Heart->setx(Heart->getx()+30);
  }
  Heart->setx(10);

  draw(avatar);

  char tampon [16] ;
  sprintf(tampon, "Score: %d", score);
  draw(tampon, S_W-175, 0, 0, 100, 0);
  for(size_t i=0;i<vect_smoke.size();i++){
    draw(vect_smoke[i]);
  }
  //avatar->setlive(0);
  if(avatar->getlive()==0){
    //draw("GAME OVER", S_H/2, S_W/2, 0, 100, 0);
    draw(GameOver);
    //draw("GAME OVER", S_W/2-80,S_H/2+75 , 250, 0, 0);
    char tampon2 [30] ;
    sprintf(tampon2, "Your Score is %d", score);
    draw(tampon2, S_W/2-100, S_H/2+110, 0, 100, 0);

    char tampon3 [30] ;
    sprintf(tampon3, "Press r for restart !!");
    draw(tampon3, S_W/2-115, S_H/2+135, 0, 100, 0);
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
