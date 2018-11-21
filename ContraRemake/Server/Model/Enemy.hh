/*
 * Enemy.hh
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#ifndef ENEMY_HH_
#define ENEMY_HH_

#include "../../Utils/ICollisional.hh"
#include "../../Utils/MessageServer.hh"
#include "CameraLogic.hh"
#include "../../Utils/Logger.hh"
#include "ServerMessageHandler.hh"
#include "Bullet.hh"
#include "../../Utils/EnemyTypesAndStates.hh"

class Enemy: public ICollisional
{
	public:

		Enemy(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, EnemyType _type, int pos_x, int pos_y);
		virtual ~Enemy();

		int getPosX() { return posX; }
		int getPosY() { return posY; }

		void render();
		void update();
		void updateCollisionBox();
		void fallingStop() { falling = false; }
		void fallingDown() { falling = true;}
		void wasHit() { dead = true; }; //ANIMACION DE MUERTO O DIRECTAMENTE BORRARLO

		bool hasNoTarget() { return !isTargetingPlayer; }
		void targetPlayer(int playerId, int playerPosX, int playerPosY);
		void updateTargetPos(int playerPosX, int playerPosY);
		int getTarget() { return targetingPlayerId; }

		bool isOnScreen() { return !cameraLogic->outOfCameraLimits(posX, posY, -40, 0, -21, 0); }

		list<Bullet*>* getBulletList() { return &bullets; }

		//Collisional
		int getLeftLimit() { return col_box_xi; }
		int getRightLimit() { return col_box_xf; }
		int getTopLimit() { return col_box_yi; }
		int getBottomLimit() { return col_box_yf; }

	private:

		ServerMessageHandler* serverMessageHandler;
		CameraLogic* cameraLogic ;

		// Manejo de balas
		std::list<Bullet*> bullets;
		std::list<Bullet*>::iterator bulletsIterator;

		bool isTargetingPlayer;
		int targetingPlayerId, targetX, targetY, targetTime;

		Uint32 lastShotTime;
		Uint32 shotCooldown;
		int distanceToTravel = 325;

		int timeAtIterationStart;
		int animation = 0;
		EnemyType type;
		int posX, posY, state, changeDirectionTime;
		bool falling, dead;

		int col_box_xi, col_box_yi, col_box_xf, col_box_yf;
};

#endif /* ENEMY_HH_ */
