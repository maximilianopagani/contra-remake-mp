#include "Game.h"

SDL_Rect srcR,desR;

Personaje* Gio;
Uint32 frameStart=0;

int globalOffset = 0;

Game::Game()
{
	enEjecucion = false;
}

Game::~Game(){}

void Game::init()
{
	enEjecucion=true;
    Gio = new Personaje();

    // A futuro a implementar esto en clase nivel o escenario
    level1Background = Grapher::loadTexture("imagenes/ContraMapStage1BGresized.png");
    // El mapa original tiene 240p pixeles de alto. Como vamos a reescalar a 800x600, para que no quede deforme, debemos llevar esos 240p a 600p (x2,5)
    // y por ende, usando la misma proporcion para que no se deforme la imagen, si queremos 800p, vamos a mostrar solo 320p de ancho de la imagen original.
    level1Rect.x = 0;
	level1Rect.y = 0;
	level1Rect.w = 320;
	level1Rect.h = 240;
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

    if(frameStart > 50)
    {
    	Gio->update();
    	SDL_Delay(100);
    }

}

void Game::update()
{
	// Actualizacion basica de background segun posicion de jugador. De nuevo, esto no va acá definitivo
	if(level1Rect.x != Gio->getPosition().x - 200)
	{
		if(Gio->getPosition().x - 200 >= 0 && Gio->getPosition().x - 200 <= 8312)
			level1Rect.x = (Gio->getPosition().x - 200)/2.5;
	}
	// Falta definir un global offset
	//level1Rect.y += Gio->getPosition().y; // para el mapa vertical, en el horizontal mostramos completo el alto, no vamos a subir ni bajar camara

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
    SDL_RenderCopy(Grapher::gameRenderer, level1Background, &level1Rect, NULL);

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

    SDL_DestroyWindow(Grapher::gameWindow);
    SDL_DestroyRenderer(Grapher::gameRenderer);
    SDL_DestroyTexture(level1Background);
    SDL_Quit();

    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
