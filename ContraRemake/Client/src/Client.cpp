//============================================================================
// Name        : Cliente.cpp
// Author      : Giova
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "TcpClient.h"
#include "View/GameView.hh"

using namespace std;


int ClientMain() {

	cout<<"Inicio Cliente"<<endl;

	//----------------------------------------------------------------------
    //Inicio la vista
	GameView* view = new GameView();
	if(!view->init())	view->destroy();

	//----------------------------------------------------------------------
	//Inicio un Cliente
	TcpClient* cliente = new TcpClient(view);
	cliente->init();

	//----------------------------------------------------------------------
    //Intento conectarme al servidor
	cliente->conecctToServer();

	//----------------------------------------------------------------------
	//Una vez conectado empiezo ciclo de recibir mensajes
	while(true){

		if ( cliente->recive() ) cout<<"Recibi un mensaje"<<endl ;

	}

	//----------------------------------------------------------------------
    //Destruyo todo lo relacionado a SDL2
	cout<<"Se cerro la vista del cliente"<<endl;
	view->destroy();

	return 0;
}
