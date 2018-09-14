#include "Game.h"


Game::Game(GameView* _gameView){
	gameView = _gameView;
	enEjecucion = false;
	level = NULL;
	player = NULL;
}

Game::~Game(){}

void Game::init(){
	enEjecucion = true;
    level = new Level(gameView, LEVEL1);
    player= new Player(gameView);
}

void Game::handleEvents(){
	SDL_Event event;

	while(SDL_PollEvent(&event)){

		if(event.type == SDL_QUIT)	enEjecucion = false ;

		else if(event.type == SDL_KEYDOWN){

			 switch(event.key.keysym.sym) {

				 case SDLK_SPACE:
					 	 player->jump();
					 	 break;

				 case SDLK_LEFT:
					 	 player->walkLeft();
					 	 break;

				 case SDLK_RIGHT:
					 	 player->walkRight();
					 	 break;

				 case SDLK_z:
					 	 player->shoot();
						 break;

				 case SDLK_DOWN:
					     player->pointDown();
						 break;

				 case SDLK_UP:
					 	 player->pointUP();
						 break;

				 case SDLK_LCTRL:
					 	 player->bodyToGround();
						 break;

				 default:
						 break;
				 }
		 }
	}
}

void Game::update(){
	player->update();
	level->updateCamera(player->getPosX(), player->getPosY());
}

void Game::render(){

	gameView->clear();

    level->render();
    player->render();

    gameView->show();
}

void Game::destroy()
{
	player->destroy();

	level->destroy();

	gameView->destroy();

	std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
