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
#include "View/ItemView.hh"
#include "View/BulletView.hh"
#include "View/EnemyView.hh"
#include "View/BossView.hh"
#include "Sound/Sound.hh"
#include "View/LivesView.hh"
#include "View/LevelTransitionView.hh"

class ClientHandler;

#include "ClientHandler.hh"

class ClientMessageHandler
{
	public:

		ClientMessageHandler();
		virtual ~ClientMessageHandler();

		void setParams(GameView* _gameView, PlayerView* _playerView, LevelView* _levelView, PlatformView* _platformView, ItemView* _itemView, BulletView* _bulletView, EnemyView* _enemyView, LivesView* _livesView, LevelTransitionView* _levelTransitionView ,BossView* _bossView , Sound* _sound);
		bool setClientHandler(ClientHandler* _client);
		void processMessage(Message* message);

	private:

		ClientHandler* client = NULL;

		GameView* gameView;
		PlayerView* playerView;
		LevelView* levelView;
		PlatformView* platformView;
		ItemView* itemView;
		BulletView* bulletView;
		EnemyView* enemyView;
		LivesView* livesView;
		LevelTransitionView* levelTransitionView;
		BossView* bossView ;

		Sound* sound;
};

#endif /* SRC_CLIENTMESSAGEHANDLER_HH_ */
