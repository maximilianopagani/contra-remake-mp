
#include "../Utils/Logger.hh"
#include "../Utils/Utils.hh"
#include "Game.hh"
#include "../Utils/ServerParser.hh"
#include "../Utils/GameParser.hh"
#include "ServerHandler.hh"

#define PUERTO 54000
#define MAX_PLAYERS 1
#define GAME_FPS 35

pthread_mutex_t server_mutex; // MUTEX GLOBAL PARA SER UTILIZADO EN SERVERHANDLER Y EN GAME CUANDO COMPARTAN ACCESO MEDIANTE DISTINTOS THREADS A LAS COLAS DE MENSAJES

int ServerMain(int argc, char* argv[])
{
	if(!Utils::initTimer())
	{
		cout<<"ServerMain: Falla al inicializar el timer."<<endl;
		return false;
	}

	server_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&server_mutex, NULL);

	ServerHandler* server = new ServerHandler(PUERTO, MAX_PLAYERS); // (PUERTO, CANTIDAD DE JUGADORES EN LA PARTIDA)
	ServerParser* serverParser = new ServerParser();
	GameParser* parser = new GameParser();

	cout<<"ServerMain: Servidor creado."<<endl;

	ServerMessageHandler* messageHandler = new ServerMessageHandler(server);

	cout<<"ServerMain: Gestionador de mensajes creado."<<endl;

	if(server->startServer())
	{
		cout<<"ServerMain: Servidor iniciado"<<endl;


		LOGGER_INIT_SETUP(Logger::DEBUG);
		if (serverParser->loadConfiguration()) {
			LOGGER_INFO("Carga de configuracion del servidor aceptada");
			serverParser->testDataServerParser();



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

	Game* synergy = new Game(server, messageHandler, MAX_PLAYERS, parser, GAME_FPS);

	cout<<"ServerMain: Juego creado."<<endl;

	server->startListeningThread();

	//----------------------------------------------------------------------

	cout<<"ServerMain: En espera de conexión de "<<synergy->getMaxPlayers()<<" jugadores."<<endl;

	while(server->getConnectedClients() != synergy->getMaxPlayers())
	{
		// Espero
	}

	//Ciclo del juego. NO DEBERIA EMPEZAR HASTA QUE SE CONECTEN TODOS LOS JUGADORES DE LA PARTIDA
	cout<<"ServerMain: Se alcanzó la cantidad de jugadores conectados necesaria. Comienza el juego."<<endl;

	synergy->init();
	cout<<"ServerMain: Juego Inicializado."<<endl;

	synergy->runGame();

	//Destruyo juego
	synergy->destroy();
	//delete server; hacer el destructor, matar todos los thread, si hubiese, y liberar recursos
	cout<<"ServerMain: Destrui el servidor"<<endl;

	return 0;
}
