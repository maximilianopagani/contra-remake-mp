#include "Game.h"

Personaje* gamePlayer;
Level* gameLevel;

Game::Game()
{
	enEjecucion = false;
}

Game::~Game(){}

void Game::init()
{
	enEjecucion = true;

    gameLevel = new Level(LEVEL1);

    gamePlayer= new Personaje();
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
    		gamePlayer->handleEvent(evento);
    	}
    }
}

void Game::update()
{
	gamePlayer->update();

	gameLevel->updateCamera(gamePlayer->getPositionX(), gamePlayer->getPositionY());

	// Actualizacion de posicion de balas
	for(gameBulletsIterator = gameBullets.begin(); gameBulletsIterator != gameBullets.end();)
	{
	    (*gameBulletsIterator)->move();

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
    gameLevel->render();

    //Copy a portion of the texture to the current rendering target.
    gamePlayer->render();

    // Renderizado de balas
	for(gameBulletsIterator = gameBullets.begin(); gameBulletsIterator != gameBullets.end();)
	{
		(*gameBulletsIterator)->render();
		++gameBulletsIterator;
	}

    //ACTUALIZA LA PANTALLA CON EL RENDER REALIZADO
    SDL_RenderPresent(Grapher::gameRenderer);
}

void Game::clean()
{
	gamePlayer->clean();

	gameLevel->clean();

    SDL_DestroyWindow(Grapher::gameWindow);
    SDL_DestroyRenderer(Grapher::gameRenderer);

    SDL_Quit();

    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
