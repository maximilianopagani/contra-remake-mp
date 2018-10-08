/*
 * LogicToViewTransporter.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_LOGICTOVIEWTRANSPORTER_HH_
#define MODEL_LOGICTOVIEWTRANSPORTER_HH_

#include "../Vista/GameView.hh"
#include "../Vista/BulletView.hh"
#include "../Vista/EnemyView.hh"
#include "../Vista/PlayerView.hh"
#include "../Vista/PlatformView.hh"
#include "../Vista/LevelView.hh"
#include "../Utils/PlayerStateHandler.hh"

enum TransportDestination {BULLETVIEW, GAMEVIEW, LEVELVIEW, PLAYERVIEW, PLATFORMVIEW, ENEMYVIEW};

class LogicToViewTransporter
{
	public:
		LogicToViewTransporter(GameView* _gameView);
		virtual ~LogicToViewTransporter();

		void sendToLoad(TransportDestination destination, string type);
		void sendToLoad(TransportDestination destination, string path, int w, int h);
		void sendToDraw(TransportDestination destination, PlayerState aState, int pos_x, int pos_y);
		void sendToDraw(TransportDestination destination, int pos_x, int pos_y);

	private:
		BulletView* bulletView;
		EnemyView* enemyView;
		PlatformView* platformView;
		PlayerView* playerView;
		GameView* gameView;
		LevelView* levelView;
};

#endif /* MODEL_LOGICTOVIEWTRANSPORTER_HH_ */
