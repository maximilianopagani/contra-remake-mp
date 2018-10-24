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

#include "ClientMain.hh"
#include "ClientLogin.hh"
#include "ClientHandler.hh"
#include "ClientMessageHandler.hh"
#include "../../Utils/Logger.hh"

using namespace std;

int ClientMain()
{
	cout<<"ClientMain: Inicio aplicacion en modo cliente."<<endl;

	ClientMessageHandler* clientMessageHandler = new ClientMessageHandler();

	cout<<"ClientMain: Gestionador de mensajes creado."<<endl;

	ClientHandler* client = new ClientHandler(clientMessageHandler);

	cout<<"ClientMain: Cliente creado."<<endl;

	if(!clientMessageHandler->setClientHandler(client))
	{
		std::cout<<"ClientMain: Falla al asociar ClientHandler con ClientMessageHandler."<<std::endl;
		delete client;
		delete clientMessageHandler;
	}

	std::cout<<"ClientMain: ClientHandler asociado con ClientMessageHandler."<<std::endl;

	if(!client->initSocket())
	{
		std::cout<<"ClientMain: Falla al inicializar el socket del cliente."<<std::endl;
		delete client;
		return 0;
	}

	cout<<"ClientMain: Socket del cliente inicializado."<<endl;

	if(clientLogin(client))
	//if(true)
	{

/*
		if (!client->connectToServer("127.0.01", 54000))
		{
			std::cout<<"ClientLogin: Falla al intentar establecer la conexión."<<std::endl;
			return false;
		}
*/

		LOGGER_INIT(Logger::ERROR);

		GameView* gameView = new GameView();

		cout<<"ClientMain: Vista principal creada."<<endl;

		if(!gameView->init())
		{
			cout<<"ClientMain: Error al iniciar GameView"<<endl;
			gameView->destroy();
			return 0;
		}

		cout<<"ClientMain: Gameview inicializado."<<endl;

		PlayerView* playerView = new PlayerView(gameView);
		LevelView* levelView = new LevelView(gameView);
		PlatformView* platformView = new PlatformView(gameView);
		BulletView* bulletView = new BulletView(gameView);
		EnemyView* enemyView = new EnemyView(gameView);

		cout<<"ClientMain: Vistas de los modulos creadas."<<endl;

		clientMessageHandler->setParams(gameView, playerView, levelView, platformView, bulletView, enemyView);

		client->run();

		cout<<"ClientMain: Cliente cerrado. Se cierra la vista del cliente"<<endl;

		delete clientMessageHandler;
		delete client;
		gameView->destroy();
	}
	return 0;
}
