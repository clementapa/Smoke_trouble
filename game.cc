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

  Ground = new Object(0,S_H-67,67,S_W,"Img/sol.jpg",ren);

  Heart = new Object(10,10,30,30,"Img/Heart2.png",ren);
  //Congrats=new Object(S_W/2-250,S_H/2-300,400,500,"Img/Congrats.png",ren);
  GameOver = new Object(S_W/2-250,S_H/2-300,400,500,"Img/GameOver2.png",ren);

  avatar = new Avatar(S_W/2-40,S_H-G_H-123,123,66,"Img/pompier.png",ren,15,10,5);

  water = new Water(S_W*10,-S_H*10,600,10,"Img/water_line.png",ren,0,0);
  Smoke = new Water(S_W*10,-S_H*10,150,150,"Img/Smoke.png",ren,0,-5);// meme mouvement que water donc pas besoin de créer une autre classe

  vect_fire.push_back(new Fire(S_W-100,100,100,100,"Img/fire.png",ren,-20,-20,3));
  vect_fire.push_back(new Fire(0,100,100,100,"Img/fire.png",ren,20,-20,3));

  /*Initialisation de la reserve de Fire*/
  for(int i=0;i<6;i++)
    reserve_fire=reserve_fire+new Fire(ren);

  /*Initialisation de la reserve de Bonus*/
  for(int i=0;i<30;i++)//50% de chance (si il y a un bonus)
    reserve_bonus=reserve_bonus+new Coin(ren);

  for(int i=0;i<20;i++)//35% de chance
    reserve_bonus=reserve_bonus+new Life(ren);

  for(int i=0;i<10;i++)//15% de chance a peu près
    reserve_bonus=reserve_bonus+new Multiplier(ren);

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
  delete Smoke;
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

  for(size_t i=0;i<vect_fire.size();i++){//update fire + collision
    vect_fire[i]->update(S_W,S_H-G_H);
    if(avatar->collision(vect_fire[i])){//collision avec avatar?
      avatar->setlive(avatar->getlive()-1);
      if(avatar->getlive()==0){
        end_game=true;
      }
      else //revenir au debut du round si l'avatar a encore au moins une vie
        init();
    }
    else if(water->collision(vect_fire[i])){//collision avec eau?
      int temp = tirage_aleatoire(reserve_bonus.size()*3);//1 chance sur 3 d'avoir un bonus
      if(temp<int(reserve_bonus.size()) && reserve_bonus.size()!=0){//Faire apparaître un bonus ou pas
        reserve_bonus[temp]->setx(vect_fire[i]->getx());
        reserve_bonus[temp]->sety(vect_fire[i]->gety());

        vect_bonus.push_back(reserve_bonus[temp]);

        reserve_bonus.erase(reserve_bonus.begin()+temp);
      }
      if((vect_fire[i]->getsize())-1!=0){//Si la taille de la flamme n'est pas de 1 (dernière taille que peut avoir une flamme avant qu'elle ne disparaise)
        //Prendre une flamme de la reserve, la modifier puis l'ajouter à vect_fire
        reserve_fire.front()->setx(vect_fire[i]->getx());
        reserve_fire.front()->sety(vect_fire[i]->gety()-50);
        reserve_fire.front()->seth(vect_fire[i]->geth()/2);
        reserve_fire.front()->setw(vect_fire[i]->getw()/2);
        reserve_fire.front()->setvx(-vect_fire[i]->getvx());
        reserve_fire.front()->setvy(-10);
        reserve_fire.front()->setsize(vect_fire[i]->getsize()-1);
        vect_fire.push_back(reserve_fire.front());//la mettre dans vect_fire

        reserve_fire.erase(reserve_fire.begin());//suprimer de la reserve
        //modifier la flamme qui a été touché
        vect_fire[i]->seth((vect_fire[i]->geth())/2);
        vect_fire[i]->setw((vect_fire[i]->getw())/2);
        vect_fire[i]->sety(vect_fire[i]->gety()-50);
        vect_fire[i]->setvy(-10);
        vect_fire[i]->setsize((vect_fire[i]->getsize())-1);
      }
      else{//Si la taille de la flamme est de 1,elle disparait et apparition d'une fumé
        Smoke->setx(vect_fire[i]->getx()+vect_fire[i]->getw()/2-Smoke->getw()/2);
        Smoke->sety(vect_fire[i]->gety()+vect_fire[i]->geth()/2-Smoke->geth()/2);
        reserve_fire.push_back(vect_fire[i]);//mettre la flamme dans la reserve pour la reutiliser après
        vect_fire.erase(vect_fire.begin()+i);//l'enlever de vect_fire pour qu'elle ne s'affiche plus

      }
      if (vect_fire.empty()) {//Si il n'y a plus de flamme dans le round bloquer le jeu, il faut appuyer sur R pour lancer le prochain round
        stop=1;
        while(stop==1){
          render();
          input();
        }
        round++;
        init();
      }
      score+=500*round*multiplier;//augmenter le score total en fonction du round et du multiplicateur de score
      /*remettre l'eau hors de l'écran si il a touché une flamme*/
      water->setx(S_W*10);
      water->sety(-S_H*10);//un y<0 pour respecter la contrainte(voir commentaire input space)
    }
  }
  /*update position avatar,water et smoke*/
  avatar->update(S_H,S_W);
  water->update(S_H,S_W);
  Smoke->update(S_H,S_W);
  /*update position des bonus et voir si collision avec avatar*/
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
        vect_bonus.erase(vect_bonus.begin()+i);// on enleve le bonus de vect_bonus
      }
    }
  }
}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}//Pour quitter le jeu avec la croix en haut à droite
    if(e.type == SDL_KEYDOWN) {//Appuyer sur une touche du clavier
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;//Echap pour quitter le jeu
      if(e.key.keysym.sym == SDLK_c){//Changement de walpaper à chaque round
        stop=0;
        if(round%3==0) wallpaper->setImage("Img/wallpaper4.jpg",ren);
        else if(round%3==1) wallpaper->setImage("Img/wallpaper3.jpg",ren);
        else wallpaper->setImage("Img/wallpaper2.jpg",ren);
      }
      if(e.key.keysym.sym == SDLK_SPACE && end_game==false){//Faire apparaître le jet d'eau en modifiant les coordonnées
        if(water->gety()<0){//Pour pas que le joueur puisse "spammer" la touche espace,il peut reappuyer sur la touche que si le jet d'eau sort de la fenêtre
          water->setx(avatar->getx() + avatar->getw()/2 - water->getw()/2);
          water->sety(avatar->gety()-G_H);
          water->setvy(-10.0);
        }
      }
      if(e.key.keysym.sym == SDLK_q && end_game==false) {//Bouger l'avatar à gauche jusqu'à que la touche soit relaché
        avatar->setx(avatar->getx()-avatar->getvx());
      }
      else if(e.key.keysym.sym == SDLK_d && end_game==false) {//Bouger l'avatar à droite jusqu'à que la touche soit relaché
        avatar->setx(avatar->getx()+avatar->getvy());
      }
      else if(e.key.keysym.sym == SDLK_r && end_game==true) {//Si plus de vie , appuyer sur R pour relancer le jeu
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
    if(e.type == SDL_KEYUP) {//Relacher la touche du clavier
      if(e.key.keysym.sym == SDLK_q && end_game==false) {//Bouger l'avatar à gauche jusqu'à que la touche soit relaché
        avatar->setx(avatar->getx()-avatar->getvx());
      }
      else if(e.key.keysym.sym == SDLK_d && end_game==false) {//Bouger l'avatar à droite jusqu'à que la touche soit relaché
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
  draw(Smoke);
  for (int i = 0; i < avatar->getlive(); i++) {
    draw(Heart);
    Heart->setx(Heart->getx()+30);//décale les coeurs pour les afficher à côté
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
