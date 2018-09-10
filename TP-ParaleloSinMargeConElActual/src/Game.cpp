#include "Game.h"
#include "CollisionObject.h"

SDL_Rect srcR,desR;


Personaje* Player;
ObjectGame* mob;
Level* level1;



std::list<ObjectGame*> mobs;

Game::Game(){}

Game::~Game(){}

void Game::init()
{
	enEjecucion = true;

    Player = new Personaje();

    level1 = new Level(SCROLLING_HORIZONTAL);

    mob = new ObjectGame();
}

void Game::catchFiredBullet(Bullet* firedBullet)
{
	gameBullets.push_back(firedBullet);
}

void Game::handleEvents()
{
	SDL_Event evento;



    while(SDL_PollEvent(&evento))
    {
    	if(evento.type == SDL_QUIT)
    	{
    		enEjecucion = false ;
    	}
    	else if(evento.type == SDL_KEYDOWN)
    	{
			Player->handleEvent(evento);

    	}
    }


}

void Game::update()
{
	Player->update();

	level1->updateCamera(Player->getPositionX(), Player->getPositionY());

	mob->update(level1->getCameraPosX());

	//checkeo coliciones a cada instante
	if( CollisionObject::CharacterCollision(Player, mob) ){
		std::cout<<"Colision!"<<std::endl;
	}


	// Actualizacion de posicion de balas
	for(gameBulletsIterator = gameBullets.begin(); gameBulletsIterator != gameBullets.end();)
	{
	    (*gameBulletsIterator)->move();

	    if( CollisionObject::BulletCollision(*gameBulletsIterator, mob) ){

	    		mob->gotCollision();
	    		delete (*gameBulletsIterator);
	    		gameBullets.erase(gameBulletsIterator);
	    		break;

	    }

	    if((*gameBulletsIterator)->outOfLimits())
	    {
	        delete (*gameBulletsIterator);
	        gameBullets.erase(gameBulletsIterator++);
	    }
	    else
	    {
	        ++gameBulletsIterator;
	    }
	}
}

void Game::render()
{
    //LIMPIA EL RENDER ENTERO CON EL COLOR QUE SE LE DIO
    SDL_RenderClear(Grapher::gameRenderer);

    //Render background
    level1->render();

    //Copy a portion of the texture to the current rendering target.
    Player->render();



    // Renderizado de balas
	for(gameBulletsIterator = gameBullets.begin(); gameBulletsIterator != gameBullets.end();)
	{
		(*gameBulletsIterator)->render();
		++gameBulletsIterator;
	}

	 //Render enemigos
	    mob->render();

    //ACTUALIZA LA PANTALLA CON EL RENDER REALIZADO
    SDL_RenderPresent(Grapher::gameRenderer);
}

void Game::clean()
{
	Player->clean();

	level1->clean();

	mob->clean();


    SDL_DestroyWindow(Grapher::gameWindow);
    SDL_DestroyRenderer(Grapher::gameRenderer);

    SDL_Quit();

    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
