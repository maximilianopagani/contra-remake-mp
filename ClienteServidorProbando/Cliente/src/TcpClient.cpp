/*
 * TcpClient.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: giova
 */

#include "TcpClient.h"

TcpClient::TcpClient(GameView* _view) {
	 network_socket = 0;
	 conecction_Status = 0;
	 view =  _view;
	 plataformView = NULL;
	 playerView= NULL;
	 levelView= NULL;
	 enemyView= NULL;
	 bulletView= NULL;
}

TcpClient::~TcpClient() {}

void TcpClient::init(){

	//-----------------------
	//Creo el Socket
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	//-----------------------
	//Asigno una direccion para el socket que acabo de crear
	server_address.sin_family =AF_INET;
	server_address.sin_port = htons(54000);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	//-----------------------
	//Vistas de cada objeto
	plataformView = new PlatformView(view);
	playerView= new PlayerView(view);
	levelView= new LevelView(view);
	enemyView= new EnemyView(view);
	bulletView= new BulletView(view);

}

void TcpClient::conecctToServer(){
	conecction_Status = connect(network_socket, (struct sockaddr *)&server_address,sizeof(server_address));
	if(conecction_Status == -1 ){
		cout << "Ocurrio un error haciendo la coneccion"<<endl;
	}else cout<<"Me conecte al servidor"<<endl;
}

bool TcpClient::Send( std::string msg ){
	int result = send(network_socket, msg.c_str(), msg.size() + 1, 0);
	if(result == -1 ){
		std::cout<<"No se mando el mensaje"<<std::endl;
		return false;
	}
	return true;
}

bool TcpClient::recive(){
	char buf[255];

	int bytesReceived = recv(network_socket, buf, sizeof(buf), 0);
	if (bytesReceived > 0){

		//-----------------------
		//Mando a filtrar el mensaje
		messageFilter(buf);

		//-----------------------
		//Mando un mensaje de "ok" al servidor para chekear que llego
		send(network_socket, "ok", 3, 0);
		return true;
	}
	return false;
}

void TcpClient::messageFilter(std::string str){

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

void TcpClient::close(){

}

