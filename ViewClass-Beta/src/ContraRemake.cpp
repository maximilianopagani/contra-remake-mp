#include "Headers.h"
#include "GameView.h"


Game* synergy;

int main(int argc, char* args[])
{
	GameView* view = new GameView();

	if(!view->init())
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

		synergy = new Game(view);

		synergy->init();

		//CICLO DEL JUEGO
		while(synergy->state())
		{
			timeAtIterationStart = view->getTricks();

			synergy->handleEvents();

			synergy->render();

			synergy->update();

			//Manejo del framerate
			iterationTime = view->getTricks() - timeAtIterationStart;

			if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
			{
				view->delay(frameDelay - iterationTime);
			}
		}

		synergy->destroy();
	}

	return 0;
}
