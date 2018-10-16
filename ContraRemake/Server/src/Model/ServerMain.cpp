
#include "../Utils/Logger.hh"
#include "../Utils/Utils.hh"
#include "Game.hh"
#include "../Utils/ServerParser.hh"
#include "../Utils/GameParser.hh"
#include "ServerHandler.hh"
#include <SDL2/SDL.h> //============= MANEJO DEL FRAMERATE =============

#define PUERTO 54000
#define MAX_PLAYERS 1

pthread_mutex_t server_mutex; // MUTEX GLOBAL PARA SER UTILIZADO EN SERVERHANDLER Y EN GAME CUANDO COMPARTAN ACCESO MEDIANTE DISTINTOS THREADS A LAS COLAS DE MENSAJES

int ServerMain(int argc, char* argv[])
{
	server_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&server_mutex, NULL);

	ServerHandler* server = new ServerHandler(PUERTO, MAX_PLAYERS); // (PUERTO, CANTIDAD DE JUGADORES EN LA PARTIDA)

	cout<<"ServerMain: Servidor creado."<<endl;

	ServerMessageHandler* messageHandler = new ServerMessageHandler(server);

	cout<<"ServerMain: Gestionador de mensajes creado."<<endl;

	Game* synergy = new Game(server, messageHandler, MAX_PLAYERS);

	cout<<"ServerMain: Juego creado."<<endl;

	if(server->startServer())
	{
		cout<<"ServerMain: Servidor iniciado"<<endl;
		ServerParser* serverParser = new ServerParser();

		LOGGER_INIT_SETUP(Logger::DEBUG);
		if (serverParser->loadConfiguration()) {
			LOGGER_INFO("Carga de configuracion del servidor aceptada");
			serverParser->testDataServerParser();

			GameParser* parser = new GameParser();

			if (parser->loadConfiguration()) {
				LOGGER_INFO("Carga de configuracion del juego aceptada");
			} else {
				cout << "Carga de configuracion del juego rechazada" << endl;
				// se mata al primer logger
				LOGGER_KILL();
				if (parser)
					delete parser;
				return 1;
			}
		} else {
			cout << "Carga de configuracion del servidor rechazada" << endl;
			// se mata al primer logger
			LOGGER_KILL();
			if (serverParser)
				delete serverParser;
			//return 1;
		}
		// se mata al primer logger
		LOGGER_KILL();
	}
	else
	{
		cout<<"ServerMain: Falla al iniciar servidor"<<endl;
		delete server;
		return 0;
	}

	server->startListeningThread();

	//----------------------------------------------------------------------

	cout<<"ServerMain: En espera de conexión de "<<synergy->getMaxPlayers()<<" jugadores."<<endl;

	while(server->getConnectedClients() != synergy->getMaxPlayers())
	{
		// Espero
	}

	//Ciclo del juego. NO DEBERIA EMPEZAR HASTA QUE SE CONECTEN TODOS LOS JUGADORES DE LA PARTIDA
	cout<<"ServerMain: Se alcanzó la cantidad de jugadores conectados necesaria. Comienza el juego."<<endl;

	//============= MANEJO DEL FRAMERATE =============
	if(SDL_Init(SDL_INIT_TIMER) != 0)
	{
		cout<<"ServerMain: Falla al inicializar SDL_TIMER"<<endl;
		return false;
	}

	const int FPS = 1;
	const int frameDelay = 1000 / FPS ;
	Uint32 timeAtIterationStart;
	int iterationTime;
	//================================================

	//----------------------------------------------------------------------

		synergy->init();
		cout<<"ServerMain: Juego Inicializado."<<endl;

	while(synergy->state())
	{
		//============= MANEJO DEL FRAMERATE =============
		timeAtIterationStart = SDL_GetTicks();
		//================================================

		//----------------------------------------------------------------------
		//Aca tengo que poner algo que reciba mensaje y los pushee
		synergy->handleEvents();

		//----------------------------------------------------------------------
		//Actualizo todo lo que vaya pasando acorde a los eventos
		synergy->update();

		//----------------------------------------------------------------------
		//Dibujo toda la escena
		synergy->render();

		//============= MANEJO DEL FRAMERATE =============
		iterationTime = SDL_GetTicks() - timeAtIterationStart;

		if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
		{
			SDL_Delay(frameDelay - iterationTime);
		}
		//================================================
	}

	//Destruyo juego
	synergy->destroy();
	//delete server; hacer el destructor, matar todos los thread, si hubiese, y liberar recursos
	cout<<"ServerMain: Destrui el servidor"<<endl;

	return 0;
}
