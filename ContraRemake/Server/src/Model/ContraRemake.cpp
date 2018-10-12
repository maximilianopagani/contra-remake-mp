
#include "../../../Utils/Logger.hh"
#include "../../../Utils/Utils.hh"
#include "Game.hh"
#include "TcpListener.h"


int ServerMain(int argc, char* argv[]){

	cout<<"Servidor Inicializado"<<endl;

	//----------------------------------------------------------------------
    //Inicio un servidor
    CTcpListener* server = new CTcpListener("127.0.0.1", 54000);
    cout<<"Servidor Creado"<<endl;

    //----------------------------------------------------------------------
    //Pongo en un ciclo escuchando hasta que se conecta un cliente
    server->clientAccept();
    cout<<"Encontre un cliente"<<endl;

    //----------------------------------------------------------------------
    //Creo el juego e inicio el ciclo del juego
    Game* synergy = new Game(server);
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
