//============================================================================
// Name        : Cliente.cpp
// Author      : Giova
//============================================================================

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ClientMain.hh"
#include "ClientLogin.hh"
#include "ClientHandler.hh"
#include "ClientMessageHandler.hh"
#include "../Utils/Logger.hh"

using namespace std;

int ClientMain()
{
	LOGGER_INFO("Inicio aplicacion en modo cliente");

	ClientMessageHandler* clientMessageHandler = new ClientMessageHandler();

	LOGGER_DEBUG("Gestionador de mensajes creado");

	ClientHandler* client = new ClientHandler(clientMessageHandler);

	LOGGER_DEBUG("Cliente creado");

	if(!clientMessageHandler->setClientHandler(client))
	{
		LOGGER_ERROR("Falla al asociar ClientHandler con ClientMessageHandler");
		delete client;
		delete clientMessageHandler;
		LOGGER_KILL();
		return 1;
	}

	LOGGER_DEBUG("ClientHandler asociado con ClientMessageHandler");

	if(!client->initSocket())
	{
		LOGGER_ERROR("Falla al inicializar el socket del cliente");
		delete client;
		LOGGER_KILL();
		return 1;
	}

	LOGGER_DEBUG("Socket del cliente inicializado");

	if(clientLogin(client))
	{

		GameView* gameView = new GameView();

		LOGGER_DEBUG("Vista principal creada");

		if(!gameView->init())
		{
			LOGGER_ERROR("Error al iniciar GameView");
			gameView->destroy();
			LOGGER_KILL();
			return 1;
		}

		LOGGER_DEBUG("Gameview inicializado");

		PlayerView* playerView = new PlayerView(gameView);
		LevelView* levelView = new LevelView(gameView);
		PlatformView* platformView = new PlatformView(gameView);
		BulletView* bulletView = new BulletView(gameView);
		EnemyView* enemyView = new EnemyView(gameView);

		LOGGER_DEBUG("Vistas de los modulos creadas");

		clientMessageHandler->setParams(gameView, playerView, levelView, platformView, bulletView, enemyView);

		client->run();

		LOGGER_INFO("Cliente cerrado. Se cierra la vista del cliente");

		delete clientMessageHandler;
		delete client;
		gameView->destroy();
	}
	LOGGER_KILL();
	return 0;
}
