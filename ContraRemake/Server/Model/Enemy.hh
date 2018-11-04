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

enum ENEMY_TYPE {
	TYPE_MOVING_ENEMY,
	TYPE_STANDING_ENEMY
};

class Enemy: public ICollisional
{
	public:

		Enemy(CameraLogic* _cameraLogic, ENEMY_TYPE _type, int _direction, int pos_x, int pos_y, ServerMessageHandler* _serverMessageHandler);
		virtual ~Enemy();

		int getPosX() { return posX; }
		int getPosY() { return posY; }

		void render();
		void update();
		void fallingStop(){falling = false; }
		void fallingDown(){falling = true;}
		void wasHit(){ dead = true; };//ANIMACION DE MUERTO O DIRECTAMENTE BORRARLO

		bool isOnScreen() { return !cameraLogic->outOfCameraLimits(posX, posY); }

		list<Bullet*>* getBulletList(){ return &bullets; }

		//Collisional
		int getLeftLimit();
		int getRightLimit();
		int getTopLimit();
		int getBottomLimit();

	private:

		ServerMessageHandler* serverMessageHandler;
		CameraLogic* cameraLogic ;

		// Manejo de balas
		std::list<Bullet*> bullets;
		std::list<Bullet*>::iterator bulletsIterator;

		int timeAtIterationStart;
		ENEMY_TYPE type;
		int posX, posY, direction;
		bool falling, dead ;
};

#endif /* ENEMY_HH_ */
