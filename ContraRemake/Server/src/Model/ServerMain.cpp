
#include "../../../Utils/Logger.hh"
#include "../../../Utils/Utils.hh"
#include "Game.hh"
#include "ServerHandler.hh"

#define PUERTO 54000

int ServerMain(int argc, char* argv[])
	{
		ServerHandler* server = new ServerHandler(PUERTO, 1); // (int PUERTO, uint CANTIDAD DE JUGADORES EN LA PARTIDA)

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


	    //----------------------------------------------------------------------
	    //Pongo en un ciclo escuchando hasta que se conecta un cliente
	    //server->clientAccept();

	    pthread_t acceptConnectionsThread;
	    pthread_create(&acceptConnectionsThread, NULL, &ServerHandler::acceptConnectionsThread, server);

	    //----------------------------------------------------------------------
	    //Creo el juego e inicio el ciclo del juego
	    Game* synergy = new Game(server, new ServerMessageHandler(server));
		synergy->init();
		cout<<"Inicio juego" <<endl<< "Empieza Loop-Game"<<endl;

		//----------------------------------------------------------------------
		//Ciclo del juego
		while(synergy->state()){

			//----------------------------------------------------------------------
			//Aca tengo que poner algo que reciba mensaje y los pushee
			synergy->handleEvents();

			//----------------------------------------------------------------------
			//Actualizo todo lo que valla pasando acorde a los eventos
			synergy->update();

			//----------------------------------------------------------------------
			//Dibujo toda la escena
			synergy->render();
		}

		//----------------------------------------------------------------------
		//Destruyo juego
		synergy->destroy();
		cout<<"Destrui el servidor"<<endl;

		return 0;
	}
