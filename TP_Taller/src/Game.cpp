#include "Game.h"

SDL_Rect srcR,desR;

Uint32 frameStart=0;

Personaje* Gio;
Level* level1;

Game::Game()
{
	enEjecucion = false;
}

Game::~Game(){}

void Game::init()
{
	enEjecucion = true;

    Gio = new Personaje();

    level1 = new Level(SCROLLING_HORIZONTAL);
}

void Game::catchFiredBullet(Bullet* firedBullet)
{
	gameBullets.push_back(firedBullet);
}

void Game::handleEvents()
{
	SDL_Event evento;

	frameStart++;

    while(SDL_PollEvent(&evento))
    {
    	if(evento.type == SDL_QUIT)
    	{
    		enEjecucion = false ;
    	}
    	else if(evento.type == SDL_KEYDOWN)
    	{
			Gio->handleEvent(evento);
			frameStart = 0; // Para que es este script de frames aca?
    	}
    }

    /*
    if(frameStart > 50)
    {
    	Gio->update();
    	SDL_Delay(100);
    }
    */
}

void Game::update()
{
	Gio->update();

	level1->updateCamera(Gio->getPositionX(), Gio->getPositionY());

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
    level1->render();

    //Copy a portion of the texture to the current rendering target.
    Gio->render();

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
	Gio->clean();

	level1->clean();

    SDL_DestroyWindow(Grapher::gameWindow);
    SDL_DestroyRenderer(Grapher::gameRenderer);

    SDL_Quit();

    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
