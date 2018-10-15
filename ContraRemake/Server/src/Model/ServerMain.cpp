
#include "../../../Utils/Logger.hh"
#include "../../../Utils/Utils.hh"
#include "Game.hh"
#include "ServerHandler.hh"
#include <SDL2/SDL.h> //============= MANEJO DEL FRAMERATE =============

#define PUERTO 54000
#define MAX_PLAYERS 1

int ServerMain(int argc, char* argv[])
{
	ServerHandler* server = new ServerHandler(PUERTO, MAX_PLAYERS); // (PUERTO, CANTIDAD DE JUGADORES EN LA PARTIDA)

	cout<<"Servidor creado"<<endl;

	if(server->startServer())
	{
		 cout<<"Servidor iniciado"<<endl;
	}
	else
	{
		cout<<"Falla al iniciar servidor"<<endl;
		delete server;
		return 0;
	}

	server->startListeningThread();

	//----------------------------------------------------------------------
	//Creo el juego e inicio el ciclo del juego
	Game* synergy = new Game(server, new ServerMessageHandler(server), MAX_PLAYERS);
	cout<<"Juego creado."<<endl;

	synergy->init();
	cout<<"Juego Inicializado."<<endl;

	//----------------------------------------------------------------------

	cout<<"En espera de conexión de "<<synergy->getMaxPlayers()<<" jugadores."<<endl;
	while(server->getConnectedClients() != synergy->getMaxPlayers())
	{
		// Espero
	}

	//Ciclo del juego. NO DEBERIA EMPEZAR HASTA QUE SE CONECTEN TODOS LOS JUGADORES DE LA PARTIDA
	cout<<"Se alcanzó la cantidad de jugadores conectados necesaria. Comienza el juego."<<endl;

	//============= MANEJO DEL FRAMERATE =============
	if(SDL_Init(SDL_INIT_TIMER) != 0)
	{
		cout<< "Falla al inicializar SDL_TIMER"<<endl;
		return false;
	}

	const int FPS = 1;
	const int frameDelay = 1000 / FPS ;
	Uint32 timeAtIterationStart;
	int iterationTime;
	//================================================

	while(synergy->state())
	{
		//============= MANEJO DEL FRAMERATE =============
		timeAtIterationStart = SDL_GetTicks();
		//================================================

		//----------------------------------------------------------------------
		//Aca tengo que poner algo que reciba mensaje y los pushee
		synergy->handleEvents();

		//----------------------------------------------------------------------
		//Actualizo todo lo que valla pasando acorde a los eventos
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
	cout<<"Destrui el servidor"<<endl;

	return 0;
}
