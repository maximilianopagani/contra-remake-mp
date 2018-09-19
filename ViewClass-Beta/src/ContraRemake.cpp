#include "GameView.hh"
#include "Headers.hh"

Game* synergy;

int main(int argc, char* args[])
{

	GameParser* parser = new GameParser();

	if (parser->loadConfiguration()) {
		parser->testDataParserModel();
	}

	GameView* view = new GameView();
	if(!view->init())
	{
		LOGGER_ERROR("Error al inicializar GameView. Se aborta ejecución.");
		view->destroy();
	}
	else
	{
		//Manejo del framerate
		const int FPS = 35;
		const int frameDelay = 1000 / FPS ;
		Uint32 timeAtIterationStart;
		int iterationTime;

		synergy = new Game(parser, view);

		synergy->init();

		//CICLO DEL JUEGO
		while(synergy->state())
		{
			timeAtIterationStart = view->getTicks();

			synergy->handleEvents();

			synergy->update();

			synergy->render();

			//Manejo del framerate
			iterationTime = view->getTicks() - timeAtIterationStart;

			if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
			{
				view->delay(frameDelay - iterationTime);
			}
		}
		synergy->destroy();
	}

	return 0;
}
