/*
 * ClientMessageHandler.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef SRC_CLIENTMESSAGEHANDLER_HH_
#define SRC_CLIENTMESSAGEHANDLER_HH_

#include "Message.hh"

#include <stdio.h>

#include "View/GameView.hh"
#include "View/PlayerView.hh"
#include "View/LevelView.hh"
#include "View/PlatformView.hh"
#include "View/BulletView.hh"
#include "View/EnemyView.hh"

class ClientHandler;

#include "ClientHandler.hh"

class ClientMessageHandler
{
	public:

		ClientMessageHandler(GameView* _gameView, PlayerView* _playerView, LevelView* _levelView, PlatformView* _platformView, BulletView* _bulletView, EnemyView* _enemyView);
		virtual ~ClientMessageHandler();

		bool setClientHandler(ClientHandler* _client);
		void processMessage(Message* message);

	private:

		ClientHandler* client = NULL;

		GameView* gameView;
		PlayerView* playerView;
		LevelView* levelView;
		PlatformView* platformView;
		BulletView* bulletView;
		EnemyView* enemyView;
};

#endif /* SRC_CLIENTMESSAGEHANDLER_HH_ */
