#include "Game.h"

SDL_Rect srcR,desR;


Personaje* Player;
Level* level1;

Game::Game(){}

Game::~Game(){}

void Game::init()
{
	enEjecucion = true;

    Player = new Personaje();

    level1 = new Level(SCROLLING_HORIZONTAL);
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
    Player->render();

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
	Player->clean();

	level1->clean();

    SDL_DestroyWindow(Grapher::gameWindow);
    SDL_DestroyRenderer(Grapher::gameRenderer);

    SDL_Quit();

    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
