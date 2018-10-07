#include "../Vista/GameView.hh"
#include "../Utils/Logger.hh"
#include "../Utils/GameParser.hh"
#include "../Utils/Utils.hh"
#include "Game.hh"

Game* synergy;

int main(int argc, char* argv[])
{
	Logger::Level logMode;
	bool hasLogMode = true;

    if (argc < 3 || std::string(argv[1]) != "-mode") {
        hasLogMode = false;
        std::cerr << "Usage: " << argv[0] << " -mode LOGGER_MODE" << std::endl;
        std::cerr << "Logger mode will be defined from configuration file" << std::endl;
    } else {
    	string arg2 = Utils::toUppercase(string(argv[2]));
    	if (arg2 == "DEBUG")
    		logMode = Logger::DEBUG;
    	else if (arg2 == "INFO")
    		logMode = Logger::INFO;
    	else if (arg2 == "ERROR")
    		logMode = Logger::ERROR;
    	else if (arg2 == "OFF")
    		logMode = Logger::OFF;
    	else
    	{
			hasLogMode = false;
			std::cerr << "Invalid mode: " << arg2 << std::endl;
			std::cerr << "Valid modes: [DEBUG, INFO, ERROR, OFF]" << std::endl;
			std::cerr << "Logger mode will be defined from configuration file" << std::endl;
    	}
    }

    if (!hasLogMode) {
		std::cerr << "Setup default mode is ERROR" << std::endl;
		LOGGER_INIT_SETUP(Logger::ERROR);
    } else
		LOGGER_INIT_SETUP(logMode);

	GameParser* parser = new GameParser();

	if (parser->loadConfiguration()) {
		LOGGER_INFO("Carga de configuracion aceptada");
	} else {
		// se mata al primer logger
		LOGGER_KILL();
		if (parser)
			delete parser;
		return 1;
	}
	// se mata al primer logger
	LOGGER_KILL();

	// si no se paso por parametro, a partir del archivo de configuracion se crea el logger deseado
    if (!hasLogMode) {
		if (parser->getLevel() == "DEBUG") {
			LOGGER_INIT(Logger::DEBUG);
		}
		else if (parser->getLevel() == "INFO") {
			LOGGER_INIT(Logger::INFO);
		}
		else if (parser->getLevel() == "ERROR") {
			LOGGER_INIT(Logger::ERROR);
		}
		else if (parser->getLevel() == "OFF") {
			LOGGER_INIT(Logger::OFF);
		}
		else {
			std::cerr << "Logger mode from configuration file is invalid" << std::endl;
			std::cerr << "Logger default mode is OFF" << std::endl;
			LOGGER_INIT(Logger::OFF);
		}
    } else
		LOGGER_INIT(logMode);



	GameView* view = new GameView();
	if(!view->init())
	{
		LOGGER_ERROR("Error al inicializar GameView. Se aborta ejecución.");
		view->destroy();
	}
	else
	{
		LogicToViewTransporter* logicToViewTransporter = new LogicToViewTransporter(view);

		//Manejo del framerate
		const int FPS = 35;
		const int frameDelay = 1000 / FPS ;
		Uint32 timeAtIterationStart;
		int iterationTime;

		synergy = new Game(parser, view, logicToViewTransporter);

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

		delete logicToViewTransporter;

		LOGGER_KILL();
	}

	return 0;
}
