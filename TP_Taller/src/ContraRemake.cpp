#include "Headers.h"

extern bool loadGrapher();

Game* synergy;

int main(int argc, char* args[])
{
	if(!loadGrapher())
	{
		printf("Failed to initialize Grapher.\n" );
	}
	else
	{
		//Manejo del framerate
		const int FPS = 40;
		const int frameDelay = 1000 / FPS ;

		Uint32 timeAtIterationStart;
		int iterationTime;

		synergy = new Game();

		synergy->init();

		//CICLO DEL JUEGO
		while(synergy->state())
		{
			timeAtIterationStart = SDL_GetTicks();

			synergy->handleEvents();
			synergy->update();
			synergy->render();

			//Manejo del framerate
			iterationTime = SDL_GetTicks() - timeAtIterationStart;

			if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
			{
				SDL_Delay(frameDelay - iterationTime);
			}
		}

		synergy->clean();
	}

	return 0;
}
