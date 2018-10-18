/*
 * ClientMessageHandler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "ClientMessageHandler.hh"

ClientMessageHandler::ClientMessageHandler(GameView* _gameView, PlayerView* _playerView, LevelView* _levelView, PlatformView* _platformView, BulletView* _bulletView, EnemyView* _enemyView)
{
	gameView = _gameView;
	playerView = _playerView;
	levelView = _levelView;
	platformView = _platformView;
	bulletView = _bulletView;
	enemyView = _enemyView;
}

bool ClientMessageHandler::setClientHandler(ClientHandler* _client)
{
	client = _client;

	if(client == NULL)
		return false;
	else
		return true;
}

ClientMessageHandler::~ClientMessageHandler() {}

void ClientMessageHandler::processMessage(Message* message)
{
	int MSG_HEADER_1, MSG_HEADER_2;
	char param1[32]; char param2[32]; char param3[32]; char param4[32];

	char msg[256];
	message->getContent(msg);

	std::cout<<"ClientMessageHandler: Procesando mensaje: "<<msg<<std::endl;

	sscanf(msg,"%i,%i,%[^,],%[^,],%[^,],%[^,];", &MSG_HEADER_1, &MSG_HEADER_2, param1, param2, param3, param4);

	switch(MSG_HEADER_1)
	{
		case PLAYER:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int estado = atoi(param1);
					int posX = atoi(param2);
					int posY = atoi(param3);
					playerView->render(estado, posX, posY);
					break;
				}
			}
			break;
		}

		case VIEW:
		{
			switch(MSG_HEADER_2)
			{
				case CLEAR:
				{
					gameView->clear();
					break;
				}

				case SHOW:
				{
					gameView->show();
					break;
				}

			}
			break;
		}

		case LEVEL:
		{
			switch(MSG_HEADER_2)
			{
				case LOAD:
				{
					int background = atoi(param2);
					levelView->loadSprite(param1, background);
					break;
				}

				case RENDER:
				{
					int pos_x = atoi(param1);
					int pos_y = atoi(param2);
					int background = atoi(param3);
					levelView->render(pos_x, pos_y, background);
					break;
				}
			}
			break;
		}

		case PLATFORM:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int posX = atoi(param1);
					int posY = atoi(param2);
					int tileAmount = atoi(param3);
					int typeCode = atoi(param4);
					platformView->render(posX, posY, tileAmount, typeCode);
					break;
				}
			}
			break;
		}

		case BULLET:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int posX = atoi(param1);
					int posY = atoi(param2);
					bulletView->render(posX, posY);
					break;
				}
			}
			break;
		}

		case REQUEST:
		{
			switch(MSG_HEADER_2)
			{
				case KEYS:
				{
					SDL_Event event;
					const Uint8* sdl_key_states;
					std::string sdl_key_string;

					while(SDL_PollEvent(&event))
					{
						if(event.type == SDL_QUIT)
						{
							client->quit();
							// avisar al server?
						}
					}
					sdl_key_states = SDL_GetKeyboardState(NULL);
					sdl_key_string = (std::to_string(sdl_key_states[SDL_SCANCODE_UP]) + std::to_string(sdl_key_states[SDL_SCANCODE_DOWN]) + std::to_string(sdl_key_states[SDL_SCANCODE_RIGHT]) + std::to_string(sdl_key_states[SDL_SCANCODE_LEFT]) + std::to_string(sdl_key_states[SDL_SCANCODE_SPACE]) + std::to_string(sdl_key_states[SDL_SCANCODE_LCTRL]) + std::to_string(sdl_key_states[SDL_SCANCODE_N]));
					// VER SI MANDAR LA TECLA DE NEXTLEVEL EN MENSAJE APARTE. O SI MANDAR TAMBIEN (EN  MENSAJE APARTE O MISMO STRING) EL EVENTO DE SDL_QUIT
					client->sendToServer(new Message(INPUT, KEYS, sdl_key_string));

					break;
				}
			}
			break;
		}
	}

	delete message;
}
