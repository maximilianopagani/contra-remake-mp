/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

//#include "Headers.h"

#ifndef PLAYER_HH_
#define PLAYER_HH_

#include "../Utils/Logger.hh"
#include "../Utils/ICollisional.hh"
#include "Bullet.hh"
#include <list>

#include "../Utils/PlayerStateHandlerServer.hh"
#include "ServerMessageHandler.hh"

class Player : public ICollisional
{
	public:

		Player(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler);
		virtual ~Player();

		//Collisional
		int getLeftLimit();
		int getRightLimit();
		int getTopLimit();
		int getBottomLimit();

		// comunes al gameloop
		void update();
		void render();
		void destroy();

		int getPosX(){ return pos_x; }
		int getPosY(){ return pos_y; }

		void spawn(int x, int y);

		//ACCIONES
		void jump();
		void goDown();
		void walkLeft();
		void walkRight();
		void pointUP(bool cond);
		void pointDefault(bool cond);
		void pointDown(bool cond);
		void bodyToGround();
		void normalState();
		void shoot();
		void fallingDownStop(){falling = false ;}
		void fallingDown(){falling = true ;}

		void handleKeys(const Uint8* _currentKeyStates);

	private:

		Uint32 timeAtIterationStart=0;

		int pos_x, pos_y, maxDistanceJump;
		bool falling;

		PlayerState state;

		enum PlayerDirection {
			DIRECTION_FRONT,
			DIRECTION_BACK
		};
		PlayerDirection direction;

		// manejo de disparo
		enum AimPosition {AIM_UP,AIM_FRONT,AIM_DOWN,AIM_BODYTOGROUND,AIM_BACK,AIM_UP_BACK,AIM_DOWN_BACK,AIM_BODYTOGROUND_BACK};
		AimPosition aimingAt;
		Uint32 lastShotTime;
		Uint32 shotCooldown;

		// Manejo de balas
		std::list<Bullet*> bullets;
		std::list<Bullet*>::iterator bulletsIterator;

		CameraLogic* cameraLogic;
		ServerMessageHandler* serverMessageHandler;

		const Uint8* currentKeyStates = NULL; // NO liberar/delete, es un puntero a un array interno de SDL
};

#endif /* PLAYER_HH_ */
