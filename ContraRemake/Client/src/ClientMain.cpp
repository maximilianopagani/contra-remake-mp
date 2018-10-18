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
#include "ClientHandler.hh"
#include "ClientMessageHandler.hh"

#define CONNECT_TO_IP	"127.0.0.1"
#define CONNECT_TO_PORT	54000

using namespace std;

int ClientMain()
{
	cout<<"ClientMain: Inicio aplicacion en modo cliente."<<endl;

	clientLogin();

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

	ClientMessageHandler* clientMessageHandler = new ClientMessageHandler(gameView, playerView, levelView, platformView, bulletView, enemyView);

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

	if(!client->connectToServer(CONNECT_TO_IP, CONNECT_TO_PORT))
	{
		std::cout<<"ClientMain: Falla al intentar establecer la conexión."<<std::endl;
		return 0;
	}

	std::cout<<"ClientMain: Conexión con el servidor establecida. Se inicia ejecución del cliente."<<std::endl;

	client->run();

	cout<<"ClientMain: Cliente cerrado. Se cierra la vista del cliente"<<endl;

	delete clientMessageHandler;
	delete client;
	gameView->destroy();

	return 0;
}
