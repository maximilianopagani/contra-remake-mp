
#include "ServerHandler.hh"
#include "Game.hh"
#include "../../Utils/ServerParser.hh"
#include "../../Utils/Logger.hh"

#define GAME_FPS 35

pthread_mutex_t server_mutex; // MUTEX GLOBAL PARA SER UTILIZADO EN SERVERHANDLER Y EN GAME CUANDO COMPARTAN ACCESO MEDIANTE DISTINTOS THREADS A LAS COLAS DE MENSAJES
pthread_mutex_t server_clients_mutex;

int ServerMain(GameParser* parser)
{
	LOGGER_INFO("Inicio aplicacion en modo servidor");
	if(!Utils::initTimer())
	{
		LOGGER_ERROR("Falla al inicializar el timer");
		LOGGER_KILL();
		return 1;
	}

	server_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&server_mutex, NULL);

	server_clients_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&server_clients_mutex, NULL);

	ServerParser* serverParser = new ServerParser();

	if (!serverParser->loadConfiguration())
	{
		LOGGER_ERROR("Falla en la carga de configuracion del serverParser");
		LOGGER_KILL();
		return 1;
	}

	ServerHandler* server = new ServerHandler(serverParser->getPort(), serverParser->getMaximumquantityclients(), serverParser->getUsers());

	LOGGER_DEBUG("Servidor creado");

	ServerMessageHandler* messageHandler = new ServerMessageHandler(server);

	LOGGER_DEBUG("Gestionador de mensajes creado");

	if(server->startServer())
	{
		LOGGER_DEBUG("Servidor iniciado");
	}
	else
	{
		LOGGER_ERROR("Falla al iniciar servidor");
		delete server;
		LOGGER_KILL();
		return 0;
	}

	Game* synergy = new Game(server, messageHandler, serverParser->getMaximumquantityclients(), parser, GAME_FPS);

	//Game* synergy = new Game(server, messageHandler, MAX_GAME_PLAYERS, parser, GAME_FPS);

	LOGGER_DEBUG("Juego creado");

	server->startListeningThread();

	//----------------------------------------------------------------------

	LOGGER_INFO("En espera de conexión de " + std::to_string(synergy->getMaxPlayers()) + " jugadores");

	while(!server->readyToStartGame())
	{
		Utils::setDelay(500);
	}

	//Ciclo del juego. NO DEBERIA EMPEZAR HASTA QUE SE CONECTEN TODOS LOS JUGADORES DE LA PARTIDA
	LOGGER_DEBUG("Se alcanzó la cantidad de jugadores conectados necesaria. Comienza el juego");

	synergy->init();
	LOGGER_DEBUG("Juego Inicializado");

	synergy->runGame();

	//Destruyo juego
	synergy->destroy();
	//delete server; hacer el destructor, matar todos los thread, si hubiese, y liberar recursos
	LOGGER_DEBUG("Servidor destruido");

	LOGGER_KILL();

	return 0;
}
