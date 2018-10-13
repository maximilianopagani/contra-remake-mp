/*
 * ClientMessageHandler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "ClientMessageHandler.hh"

ClientMessageHandler::ClientMessageHandler(ClientHandler* _client)
{
	client = _client;
}

void ClientMessageHandler::sendToServer(Message* message)
{
	client->sendToServer(message);
}

ClientMessageHandler::~ClientMessageHandler() {
	// TODO Auto-generated destructor stub
}

void ClientMessageHandler::redirectRecievedMessage(Message* message)
{
/*
 * void TcpClient::messageFilter(std::string str){

	std::string messageParts[5];
	int indice = 0 ;

	//-----------------------
	//Separo por comas el mensaje
	char* token = strtok(const_cast<char*>(str.c_str()), ",");
	while( token!= nullptr){
		//message.push_back(std::string(token));
		messageParts[indice] = token ;
		token = strtok(nullptr,",");
		indice++;
	}
	indice = 0;

	//-----------------------
	//Mensaje para jugador
	if( messageParts[0]=="player" ){
		std::cout<<"mesaje para jugador"<<std::endl;
		//playerView->render(6, 150, 150);

		int estado = atoi( messageParts[1].c_str() );
		int posX = atoi( messageParts[2].c_str() );
		int posY = atoi( messageParts[3].c_str() );

		playerView->render(estado, posX, posY);
		view->show();
	}

	//-----------------------
	//Mensaje para GameVIew
	if( messageParts[0] == "gameview" ){
		std::cout<<"mesaje para GameView"<<std::endl;

		if( messageParts[1] == "clear" ){
			std::cout<<"CLEAR"<<std::endl;
			view->clear();
		}
	}

	//-----------------------
	//Mensaje para Plataforma
	if( messageParts[0] == "plataforma"){
			std::cout<<"mesaje para plataforma"<<std::endl;
	}

	//-----------------------
	//Mensaje para Level
	if(  messageParts[0] == "level" ){
			std::cout<<"mesaje para level"<<std::endl;
	}

	//-----------------------
	//Mensaje para Enemy
	if(  messageParts[0] == "enemy"){
			std::cout<<"mesaje para enemy"<<std::endl;
	}

	//-----------------------
	//Mensaje para Bullet
	if(  messageParts[0] == "bullet"){
			std::cout<<"mesaje para bullet"<<std::endl;
	}

	std::cout<<"mesaje spliteado : "<<std::endl;
	for(int j=0 ; j <5 ; j++){
		cout<<messageParts[j]<<endl;
	}
}
*/
}
