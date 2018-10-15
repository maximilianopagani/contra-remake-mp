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

ClientMessageHandler::~ClientMessageHandler() {}

void ClientMessageHandler::redirectRecievedMessage(Message* message)
{
	int MSG_HEADER_1, MSG_HEADER_2;
	char param2[32]; char param3[32]; char param4[32]; char param5[32]; char param6[32];

	char msg[256];
	message->getContent(msg);

	std::cout<<"ClientMessageHandler: Procesando mensaje: "<<msg<<std::endl;

	sscanf(msg,"%i,%i,%[^,],%[^,],%[^,],%[^,],%[^;];", &MSG_HEADER_1, &MSG_HEADER_2, param2, param3, param4, param5, param6);

	switch(MSG_HEADER_1)
	{
		case PLAYER:
		{
			switch(MSG_HEADER_2)
			{
				case RENDER:
				{
					int estado = atoi(param2);
					int posX = atoi(param3);
					int posY = atoi(param4);

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
	}

	delete message;
}
