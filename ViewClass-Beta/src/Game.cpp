#include "Game.h"


Game::Game(GameView* _gameView){
	gameView = _gameView;
	keyhanlder = NULL;
	enEjecucion = false;
	level = NULL;
	player = NULL;
}

Game::~Game(){}

void Game::init(){
	enEjecucion = true;
    level = new Level(gameView, LEVEL1);
    player= new Player(gameView);
    keyhanlder = new KeyEventHandler();
    keyhanlder->clean();
}

void Game::handleEvents(){
	SDL_Event event;

	while(SDL_PollEvent(&event)){



		if(event.type == SDL_QUIT)	enEjecucion = false ;

		else if(event.type == SDL_KEYDOWN){

			 switch(event.key.keysym.sym) {

				 case SDLK_SPACE:
					 	// std::cout<<event.key.keysym.scancode<<std::endl;
					 	 keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
					 	 break;

				 case SDLK_LEFT:
					 	// std::cout<<event.key.keysym.scancode<<std::endl;
					 	 keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
					 	 break;

				 case SDLK_RIGHT:
					 	 //std::cout<<event.key.keysym.scancode<<std::endl;
					 	 keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
					 	 break;

				 case SDLK_z:
					 	// std::cout<<event.key.keysym.scancode<<std::endl;
					 	 keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
						 break;

				 case SDLK_DOWN:
					    // std::cout<<event.key.keysym.scancode<<std::endl;
					      keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
						 break;

				 case SDLK_UP:
					 	// std::cout<<event.key.keysym.scancode<<std::endl;
					 	 keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
						 break;

				 case SDLK_LCTRL:
					 	// std::cout<<event.key.keysym.scancode<<std::endl;
					 	 keyhanlder->setState( event.key.keysym.scancode, SDL_PRESSED);
						 break;

				 default:
						 break;
				 }
		 }
		/**********************/





		/**********************/

		else if(event.type == SDL_KEYUP){

					 switch(event.key.keysym.sym) {

						 case SDLK_SPACE:
							 	 std::cout<<event.key.keysym.scancode<<std::endl;
							 	 keyhanlder->setState( event.key.keysym.scancode, 0);
							 	 break;

						 case SDLK_LEFT:
							 	 std::cout<<event.key.keysym.scancode<<std::endl;
							 	 keyhanlder->setState( event.key.keysym.scancode, 0);
							 	 break;

						 case SDLK_RIGHT:
							 	 std::cout<<event.key.keysym.scancode<<std::endl;
							 	 keyhanlder->setState( event.key.keysym.scancode, 0);
							 	 break;

						 case SDLK_z:
							 	 std::cout<<event.key.keysym.scancode<<std::endl;
							 	 keyhanlder->setState( event.key.keysym.scancode, 0);
								 break;

						 case SDLK_DOWN:
							     std::cout<<event.key.keysym.scancode<<std::endl;
							      keyhanlder->setState( event.key.keysym.scancode, 0);
								 break;

						 case SDLK_UP:
							 	 std::cout<<event.key.keysym.scancode<<std::endl;
							 	 keyhanlder->setState( event.key.keysym.scancode, 0);
								 break;

						 case SDLK_LCTRL:
							 	 std::cout<<event.key.keysym.scancode<<std::endl;
							 	 keyhanlder->setState( event.key.keysym.scancode, 0);
								 break;

						 default:
								 break;
						 }
				 }

	}


	if(keyhanlder->getState(79)==1&&keyhanlder->getState(29)==1 ){
				std::cout<<"ENtre"<<std::endl;
				//player->test();
			player->walkRight();
			player->shoot();
			}

	/*if(keyhanlder->getState(29)) player->shoot();
	else if(keyhanlder->getState(44)) player->jump();
	else if(keyhanlder->getState(44)&&keyhanlder->getState(29)) {
		player->jump();
		player->shoot();
	}
	else if(keyhanlder->getState(79)) {
		player->walkRight();
	}
	else if(keyhanlder->getState(79)&& keyhanlder->getState(29)) {
			player->walkRight();
			player->shoot();
		}
	else if(keyhanlder->getState(80)) {
			player->walkLeft();
	}
	else if(keyhanlder->getState(80)&&keyhanlder->getState(29)){
		player->test();
		player->test2();
		player->shoot();
	}*/



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
