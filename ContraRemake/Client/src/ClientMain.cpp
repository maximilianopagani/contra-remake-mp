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
#include "View/GameView.hh"

using namespace std;


int ClientMain()
{
	cout<<"Inicio Cliente"<<endl;

	//----------------------------------------------------------------------
    //Inicio la vista
	GameView* view = new GameView();
	if(!view->init())	view->destroy();

	//----------------------------------------------------------------------
	//Inicio un Cliente
	ClientHandler* client = new ClientHandler();

	if(!client->initSocket())
	{
		std::cout<<"Falla al inicializar el cliente."<<std::endl;
		return 0;
	}

	//----------------------------------------------------------------------
    //Intento conectarme al servidor
	if(!client->connectToServer("127.0.0.1", 54000))
	{
		std::cout<<"Falla al intentar establecer la conexión."<<std::endl;
		return 0;
	}

	//----------------------------------------------------------------------
	//CICLO DEL JUEGO

	const int FPS = 35;
	const int frameDelay = 1000 / FPS ;
	Uint32 timeAtIterationStart;
	int iterationTime;

	bool en_ejecucion = true;

	const Uint8* sdl_key_states;

	SDL_Event event;

	/*
	enum GAME_KEY {
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_SPACE,
		KEY_LCTRL,
		KEY_N
	};

	int client_key_states[7];
	*/

	while(en_ejecucion)
	{
		timeAtIterationStart = view->getTicks();

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				en_ejecucion = false ;
			}
		}

		sdl_key_states = SDL_GetKeyboardState(NULL);

		/*
		client_key_states[KEY_UP] = sdl_key_states[SDL_SCANCODE_UP];
		client_key_states[KEY_DOWN] = sdl_key_states[SDL_SCANCODE_DOWN];
		client_key_states[KEY_RIGHT] = sdl_key_states[SDL_SCANCODE_RIGHT];
		client_key_states[KEY_LEFT] = sdl_key_states[SDL_SCANCODE_LEFT];
		client_key_states[KEY_SPACE] = sdl_key_states[SDL_SCANCODE_SPACE];
		client_key_states[KEY_LCTRL] = sdl_key_states[SDL_SCANCODE_LCTRL];
		client_key_states[KEY_N] = sdl_key_states[SDL_SCANCODE_N];
		*/

		//Manejo del framerate
		iterationTime = view->getTicks() - timeAtIterationStart;

		if(frameDelay > iterationTime) // Si lo que tardó la iteracion es menor a lo que debe tardar un ciclo para mostrarse a la tasa de frames deseada
		{
			view->delay(frameDelay - iterationTime);
		}

		client->sendToServer(new Message(INFO, KEYS, (std::to_string(sdl_key_states[SDL_SCANCODE_UP]) + std::to_string(sdl_key_states[SDL_SCANCODE_DOWN]) + std::to_string(sdl_key_states[SDL_SCANCODE_RIGHT]) + std::to_string(sdl_key_states[SDL_SCANCODE_LEFT]) + std::to_string(sdl_key_states[SDL_SCANCODE_SPACE]) + std::to_string(sdl_key_states[SDL_SCANCODE_LCTRL]) + std::to_string(sdl_key_states[SDL_SCANCODE_N])))); // @suppress("Function cannot be resolved")

	}

	//----------------------------------------------------------------------
    //Destruyo todo lo relacionado a SDL2
	cout<<"Se cerro la vista del cliente"<<endl;
	view->destroy();

	return 0;
}
