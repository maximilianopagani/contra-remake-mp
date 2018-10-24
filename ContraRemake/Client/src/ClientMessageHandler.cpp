/*
 * ClientMessageHandler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "ClientMessageHandler.hh"

ClientMessageHandler::ClientMessageHandler()
{
	gameView = NULL;
	playerView = NULL;
	levelView = NULL;
	platformView = NULL;
	bulletView = NULL;
	enemyView = NULL;
}

void ClientMessageHandler::setParams(GameView* _gameView, PlayerView* _playerView, LevelView* _levelView, PlatformView* _platformView, BulletView* _bulletView, EnemyView* _enemyView)
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
	string sep = ": ";
	LOGGER_DEBUG("Procesando mensaje recibido del servidor" + sep + msg);

	sscanf(msg,"%i,%i,%[^,],%[^,],%[^,],%[^,];", &MSG_HEADER_1, &MSG_HEADER_2, param1, param2, param3, param4);

	switch(MSG_HEADER_1)
	{
		case PLAYER:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int player_id = atoi(param1);
					int estado = atoi(param2);
					int posX = atoi(param3);
					int posY = atoi(param4);
					playerView->render(player_id, estado, posX, posY);
					break;
				}
				case LOAD:
				{
					int player_id = atoi(param1);
					int estado = atoi(param2);
					playerView->update(player_id, estado);
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
						}
					}

					sdl_key_states = SDL_GetKeyboardState(NULL);
					sdl_key_string = (std::to_string(sdl_key_states[SDL_SCANCODE_UP]) + std::to_string(sdl_key_states[SDL_SCANCODE_DOWN]) + std::to_string(sdl_key_states[SDL_SCANCODE_RIGHT]) + std::to_string(sdl_key_states[SDL_SCANCODE_LEFT]) + std::to_string(sdl_key_states[SDL_SCANCODE_SPACE]) + std::to_string(sdl_key_states[SDL_SCANCODE_LCTRL]) + std::to_string(sdl_key_states[SDL_SCANCODE_N]));
					client->sendToServer(new Message(INPUT, KEYS, sdl_key_string));
					break;
				}
				case LOGIN:
				{
					client->sendToServer(new Message(INFO, LOGIN, client->getUsername(), client->getPassword()));
					break;
				}
			}
			break;
		}

		case ERROR:
		{
			switch(MSG_HEADER_2)
			{
				case LOGIN:
				{
					client->quit();
					break;
				}
			}
			break;
		}
		case INFO:
		{
			switch(MSG_HEADER_2)
			{
				case WAITINGPLAYERS:
				{
					client->initPulse = true;
					break;
				}
			}
			break;
		}
	}

	delete message;
}
