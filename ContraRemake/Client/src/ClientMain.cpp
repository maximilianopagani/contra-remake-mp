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

#include "ClientHandler.hh"
#include "ClientMessageHandler.hh"

using namespace std;


int ClientMain()
{
	cout<<"ClientMain: Inicio aplicacion en modo cliente."<<endl;

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

	if(!client->initSocket())
	{
		std::cout<<"ClientMain: Falla al inicializar el socket del cliente."<<std::endl;
		delete client;
		return 0;
	}

	cout<<"ClientMain: Socket del cliente inicializado."<<endl;

	if(!client->connectToServer("127.0.0.1", 54000))
	{
		std::cout<<"ClientMain: Falla al intentar establecer la conexión."<<std::endl;
		return 0;
	}

	std::cout<<"ClientMain: Conexión con el servidor establecida."<<std::endl;

	//CICLO DEL JUEGO

	const int FPS = 1;
	const int frameDelay = 1000 / FPS ;
	Uint32 timeAtIterationStart;
	int iterationTime;

	bool en_ejecucion = true;

	const Uint8* sdl_key_states;

	SDL_Event event;

	while(en_ejecucion)
	{
		timeAtIterationStart = gameView->getTicks();

		//===================== EVENTOS =======================
		std::cout<<"ClientMain: Inicio de procesamiento de eventos y teclas."<<std::endl;

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				en_ejecucion = false;
			}
		}

		sdl_key_states = SDL_GetKeyboardState(NULL);

		client->sendToServer(new Message(INPUT, KEYS, (std::to_string(sdl_key_states[SDL_SCANCODE_UP]) + std::to_string(sdl_key_states[SDL_SCANCODE_DOWN]) + std::to_string(sdl_key_states[SDL_SCANCODE_RIGHT]) + std::to_string(sdl_key_states[SDL_SCANCODE_LEFT]) + std::to_string(sdl_key_states[SDL_SCANCODE_SPACE]) + std::to_string(sdl_key_states[SDL_SCANCODE_LCTRL]) + std::to_string(sdl_key_states[SDL_SCANCODE_N])))); // @suppress("Function cannot be resolved")

		std::cout<<"ClientMain: Fin de procesamiento de eventos y teclas."<<std::endl;

		//=====================================================

		//Manejo del framerate
		iterationTime = gameView->getTicks() - timeAtIterationStart;

		if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
		{
			gameView->delay(frameDelay - iterationTime);
		}
	}

	//----------------------------------------------------------------------
    //Destruyo todo lo relacionado a SDL2
	cout<<"Se cerro la vista del cliente"<<endl;

	gameView->destroy();

	return 0;
}
