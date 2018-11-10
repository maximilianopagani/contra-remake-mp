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
	itemView = NULL;
	bulletView = NULL;
	enemyView = NULL;
	livesView = NULL;
	sound = NULL;
	levelTransitionView = NULL;
}

void ClientMessageHandler::setParams(GameView* _gameView, PlayerView* _playerView, LevelView* _levelView, PlatformView* _platformView, ItemView* _itemView, BulletView* _bulletView, EnemyView* _enemyView, LivesView* _livesView, LevelTransitionView* _levelTransitionView)
{
	gameView = _gameView;
	playerView = _playerView;
	levelView = _levelView;
	platformView = _platformView;
	itemView = _itemView;
	bulletView = _bulletView;
	enemyView = _enemyView;
	livesView = _livesView;
	sound = new Sound();
	levelTransitionView = _levelTransitionView;
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

		case ITEM:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int posX = atoi(param1);
					int posY = atoi(param2);
					int type = atoi(param3);
					itemView->render(posX, posY, type);
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
					int player_id = atoi(param1);
					int posX = atoi(param2);
					int posY = atoi(param3);
					bulletView->render(player_id, posX, posY);
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
					sdl_key_string = (std::to_string(sdl_key_states[SDL_SCANCODE_UP]) + std::to_string(sdl_key_states[SDL_SCANCODE_DOWN]) + std::to_string(sdl_key_states[SDL_SCANCODE_RIGHT]) + std::to_string(sdl_key_states[SDL_SCANCODE_LEFT]) + std::to_string(sdl_key_states[SDL_SCANCODE_SPACE]) + std::to_string(sdl_key_states[SDL_SCANCODE_LCTRL]) + std::to_string(sdl_key_states[SDL_SCANCODE_I]) + std::to_string(sdl_key_states[SDL_SCANCODE_N]));
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
				case LOGIN_DATA:
				{
					gameView->showInvalidLoginScreen();
					client->quit(3000);
					break;
				}
				case LOGIN_ALREADY_ON:
				{
					gameView->showAlreadyConnectedScreen();
					client->quit(3000);
					break;
				}
				case GAME_FULL:
				{
					gameView->showGameFullScreen();
					client->quit(3000);
					break;
				}
				case LOST_CONNECTION:
				{
					gameView->showDisconnectedScreen();
					client->quit(3000);
					break;
				}
			}
			break;
		}

		case INFO:
		{
			switch(MSG_HEADER_2)
			{
				case WAITING_PLAYERS:
				{
					gameView->showWaitingPlayersScreen();
					sound->play(0,0,0, 50);
					client->initPulse = true;
					break;
				}
				case RECONNECT_SUCCESS:
				{
					client->initPulse = true;
					break;
				}
				case SERVER_CLOSED:
				{
					gameView->showServerClosedScreen();
					client->quit(3000);
				}
			}
			break;
		}

		case ENEMY:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int enemy_type = atoi(param1);
					int state = atoi(param2);
					int pos_x = atoi(param3);
					int pos_y = atoi(param4);
					enemyView->render(enemy_type, state, pos_x, pos_y);
					break;
				}
				case LOAD:
				{
					int enemy_type = atoi(param1);
					int state = atoi(param2);
					enemyView->update(enemy_type, state);
					break;
				}
			}
			break;
		}

		case LIVES:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int player_id = atoi(param1);
					int amount = atoi(param2);
					livesView->render(player_id, amount);
					break;
				}
			}
			break;
		}
		case SOUND:
		{
			switch(MSG_HEADER_2)
			{
				case LOAD:
				{
					int type = atoi(param1);
					int subtype = atoi(param2);
					sound->play(type,subtype, 0, 50);
					break;
				}
			}
			break;
		}
		case LEVELTRANSITION:
		{
			switch(MSG_HEADER_2)
			{
				case LOAD:
				{
					int level_id = atoi(param1);
					int player_id = atoi(param2);
					int score = atoi(param3);
					levelTransitionView->loadScore(level_id, player_id, score);
					break;
				}
				case RENDER:
				{
					levelTransitionView->render();
					break;
				}
			}
		}
	}

	delete message;
}
