#include <string>
#include "game.hh"
#include "utility.hh"

using namespace std;

template <class T,class U>
vector<T*> operator+(vector<T*> lhs, U* rhs)
{
  lhs.push_back(rhs);
  return lhs;
}

template <class T,class U>
list<T*> operator+(list<T*> lhs, U* rhs)
{
  lhs.push_back(rhs);
  return lhs;
}

Game::Game() {

  SDL_Init(0);
  SDL_CreateWindowAndRenderer(S_W, S_H, 0, &win, &ren);//w=480(largeur) h=720 longueur
  SDL_SetWindowTitle(win, "Fire trouble!!!");
  TTF_Init();
  running=true;
  stop=0;
  round=1;
  multiplier=1;
  time=0;


  wallpaper = new Object(0.0,0.0,S_H,S_W,"Img/wallpaper4.jpg",ren);
  //Loading = new Object(0.0,0.0,S_H,S_W,"Img/Loading.png",ren);
  //draw(Loading);
  Ground = new Object(0,S_H-67,67,S_W,"Img/sol.jpg",ren);

  Heart = new Object(10,10,30,30,"Img/Heart2.png",ren);
  //Congrats=new Object(S_W/2-250,S_H/2-300,400,500,"Img/Congrats.png",ren);
  GameOver = new Object(S_W/2-250,S_H/2-300,400,500,"Img/GameOver2.png",ren);

  avatar = new Avatar(S_W/2-40,S_H-G_H-123,123,66,"Img/pompier.png",ren,15,10,5);

  water = new Water(S_W*10,-S_H*10,600,10,"Img/water_line.png",ren,0,0);
  SMoke = new Water(S_W*10,-S_H*10,150,150,"Img/Smoke.png",ren,0,-5);

  vect_fire.push_back(new Smoke(S_W-100,100,100,100,"Img/fire.png",ren,-20,-20,3));
  vect_fire.push_back(new Smoke(0,100,100,100,"Img/fire.png",ren,20,-20,3));

  for(int i=0;i<6;i++)
    reserve_fire=reserve_fire+new Smoke(ren);
  //cout<<reserve_fire.size()<<endl;

  for(int i=0;i<30;i++){
    //reserve_bonus.push_back(new Coin(ren));
    reserve_bonus=reserve_bonus+new Coin(ren);
  }
  for(int i=0;i<20;i++){
    //reserve_bonus.push_back(new Life(ren));
    reserve_bonus=reserve_bonus+new Life(ren);
  }
  for(int i=0;i<10;i++){
    //reserve_bonus.push_back(new Multiplier(ren));
    reserve_bonus=reserve_bonus+new Multiplier(ren);
  }
  //cout<<reserve_bonus.size()<<endl;

  font = TTF_OpenFont("font/Sans3.ttf", 24);
  end_game=false;
  score=0;
    loop();
}


void Game::init(){

/*Je vide mon vect fire en mettant les fires dans la reserve*/
  size_t size=vect_fire.size();
  for(size_t i=0;i<size;i++){
    reserve_fire.push_back(vect_fire[i]);
    //std::cout << "for" << '\n';
  }
  vect_fire.clear();
  /*je remets l avatar au milieu du jeu*/
  avatar->setx(S_W/2-40);

/*je prend les deux premieres flamme de la reserve et je les transforme en grandes flamme*/
/*puis je les push dans vect fire*/
  reserve_fire.front()->setx(S_W-100);
  reserve_fire.front()->sety(100);
  reserve_fire.front()->seth(100);
  reserve_fire.front()->setw(100);
  reserve_fire.front()->setvx(-20 -round*3);
  reserve_fire.front()->setvy(-20);
  reserve_fire.front()->setsize(3);

  vect_fire.push_back(reserve_fire.front());
  reserve_fire.erase(reserve_fire.begin());

  reserve_fire.front()->setx(0);
  reserve_fire.front()->sety(100);
  reserve_fire.front()->seth(100);
  reserve_fire.front()->setw(100);
  reserve_fire.front()->setvx(20+round*3);
  reserve_fire.front()->setvy(-20);
  reserve_fire.front()->setsize(3);

  vect_fire.push_back(reserve_fire.front());
  reserve_fire.erase(reserve_fire.begin());
}


Game::~Game() {
  TTF_Quit();
  delete wallpaper;
  delete Heart;
  delete Ground;
  delete GameOver;
  delete avatar;
  delete water;
  delete SMoke;
  for(size_t i;i<vect_fire.size();i++)
    delete vect_fire[i];
  for(size_t i;i<reserve_fire.size();i++)
    delete reserve_fire.front();
  for(size_t i;i<vect_bonus.size();i++)
    delete vect_bonus[i];
  for(size_t i;i<reserve_bonus.size();i++)
    delete reserve_bonus[i];

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
    if(!end_game) time+=1;

    input();
    render();
    update();
  }
}

void Game::update(){

  for(size_t i=0;i<vect_fire.size();i++){
    vect_fire[i]->update(S_W,S_H-G_H);
    if(avatar->collision(vect_fire[i])){
      avatar->setlive(avatar->getlive()-1);
      if(avatar->getlive()==0){
        end_game=true;
      }
      else //revenir au debut du round si l'avatar a encore au moins une vie
        init();
    }
    else if(water->collision(vect_fire[i])){
      int temp = tirage_aleatoire(reserve_bonus.size()*3);//1/3 d'avoir un bonus
      if(temp<int(reserve_bonus.size()) && reserve_bonus.size()!=0){
        reserve_bonus[temp]->setx(vect_fire[i]->getx());
        reserve_bonus[temp]->sety(vect_fire[i]->gety());

        vect_bonus.push_back(reserve_bonus[temp]);

        reserve_bonus.erase(reserve_bonus.begin()+temp);
      }
      if((vect_fire[i]->getsize())-1!=0){

        reserve_fire.front()->setx(vect_fire[i]->getx());
        reserve_fire.front()->sety(vect_fire[i]->gety()-50);
        reserve_fire.front()->seth(vect_fire[i]->geth()/2);
        reserve_fire.front()->setw(vect_fire[i]->getw()/2);
        reserve_fire.front()->setvx(-vect_fire[i]->getvx());
        reserve_fire.front()->setvy(-10);
        reserve_fire.front()->setsize(vect_fire[i]->getsize()-1);
        vect_fire.push_back(reserve_fire.front());

        reserve_fire.erase(reserve_fire.begin());

        vect_fire[i]->seth((vect_fire[i]->geth())/2);
        vect_fire[i]->setw((vect_fire[i]->getw())/2);
        vect_fire[i]->sety(vect_fire[i]->gety()-50);
        vect_fire[i]->setvy(-10);
        vect_fire[i]->setsize((vect_fire[i]->getsize())-1);
      }
      else{
        SMoke->setx(vect_fire[i]->getx()+vect_fire[i]->getw()/2-SMoke->getw()/2);
        SMoke->sety(vect_fire[i]->gety()+vect_fire[i]->geth()/2-SMoke->geth()/2);
        reserve_fire.push_back(vect_fire[i]);
        vect_fire.erase(vect_fire.begin()+i);

      }
      if (vect_fire.empty()) {
        stop=1;
        while(stop==1){
          render();
          input();
        }
        round++;
        init();
      }
      score+=500*round*multiplier;
      water->setx(S_W*10);
      water->sety(-S_H*10);
    }
  }
  avatar->update(S_H,S_W);
  water->update(S_H,S_W);
  SMoke->update(S_H,S_W);
  if(!vect_bonus.empty()){
    for(size_t i=0;i<vect_bonus.size();i++){
      vect_bonus[i]->update(S_H,S_W);
      if(avatar->collision(vect_bonus[i])){
        if(vect_bonus[i]->get_name()=="Multiplier"){
          multiplier+=2;
        }
        else if(vect_bonus[i]->get_name()=="Coin"){
          score=score+1000*multiplier;
        }
        else if(vect_bonus[i]->get_name()=="Life"){
          avatar->setlive(avatar->getlive()+1);
        }
        vect_bonus.erase(vect_bonus.begin()+i);
      }
    }
  }
}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
      if(e.key.keysym.sym == SDLK_c){
        stop=0;
        if(round%3==0) wallpaper->setImage("Img/wallpaper4.jpg",ren);
        else if(round%3==1) wallpaper->setImage("Img/wallpaper3.jpg",ren);
        else wallpaper->setImage("Img/wallpaper2.jpg",ren);
      }
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
      else if(e.key.keysym.sym == SDLK_r && end_game==true) {
        avatar->setlive(5);
        score=0;
        round=1;
        multiplier=1;
        time=0;
        end_game=false;
        wallpaper->setImage("Img/wallpaper4.jpg",ren);
        init();
      }

    }
    if(e.type == SDL_KEYUP) {
      if(e.key.keysym.sym == SDLK_q && end_game==false) {
        avatar->setx(avatar->getx()-avatar->getvx());
      }
      else if(e.key.keysym.sym == SDLK_d && end_game==false) {
        avatar->setx(avatar->getx()+avatar->getvy());
      }
    }
     SDL_GetMouseState(&mousex, &mousey);
  }
}

void Game::render() {

  draw(wallpaper);
  if (stop==0) draw(water);
  draw(Ground);
  draw(SMoke);
  for (int i = 0; i < avatar->getlive(); i++) {
    draw(Heart);
    Heart->setx(Heart->getx()+30);
  }
  Heart->setx(10);

  draw(avatar);
  if(!vect_bonus.empty()){
    for(size_t i=0;i<vect_bonus.size();i++)
      draw(vect_bonus[i]);
  }

  char tampon [16] ;
  sprintf(tampon, "Score: %d", score);
  draw(tampon, S_W-175, 0, 0, 100, 0);

  sprintf(tampon, "Round: %d", round);
  draw(tampon, S_W-175, 50, 0, 100, 0);

  sprintf(tampon, "Multiplier: %d", multiplier);
  draw(tampon, S_W-175, 100, 0, 100, 0);

  sprintf(tampon, "Time: %d", time);
  draw(tampon, 10, 50, 0, 100, 0);

  for(size_t i=0;i<vect_fire.size();i++){
    draw(vect_fire[i]);
  }
  //avatar->setlive(0);
  if(end_game==true){
    //draw("GAME OVER", S_H/2, S_W/2, 0, 100, 0);
    draw(GameOver);
    //draw("GAME OVER", S_W/2-80,S_H/2+75 , 250, 0, 0);
    char tampon2 [30] ;
    sprintf(tampon2, "Your Score is %d", score);
    draw(tampon2, S_W/2-100, S_H/2+110, 0, 100, 0);

    sprintf(tampon2, "Round: %d", round);
    draw(tampon2,S_W/2-50, S_H/2+80, 0, 100, 0);

    char tampon3 [30] ;
    sprintf(tampon3, "Press r for restart !!");
    draw(tampon3, S_W/2-130, S_H/2+135, 0, 100, 0);
  }

  if(stop==1){
    char tampon2 [30] ;
    sprintf(tampon2, "Your Score is %d", score);
    draw(tampon2, S_W/2-100, S_H/2+100, 0, 100, 0);

    char tampon3 [30] ;
    sprintf(tampon3, "Press C to coninue !!");
    draw(tampon3, S_W/2-100, S_H/2+125, 0, 100, 0);
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
