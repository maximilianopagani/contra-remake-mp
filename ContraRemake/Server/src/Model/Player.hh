/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

//#include "Headers.h"

#ifndef PLAYER_HH_
#define PLAYER_HH_

#include "../../../Utils/PlayerStateHandler.hh"
#include "../../../Utils/Logger.hh"
#include "../../../Utils/ICollisional.hh"
#include "Bullet.hh"
#include "ServerMessageHandler.hh"

class Player : public ICollisional
{
	public:

		Player(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, int _player_id);
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
		int getState(){ return state;}

		void spawn(int x, int y);
		void freeze();
		void IsFreezed(bool vertical);

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

		void handleKeys(const Uint8* playerKeyStates);
		bool alreadyProcessedKeys() { return processedKeys; }

	private:

		int player_id;
		int pos_x, pos_y, maxDistanceJump;
		bool falling;

		Uint32 timeAtIterationStart=0;

		PlayerState state;

		enum PlayerDirection {
			DIRECTION_FRONT,
			DIRECTION_BACK
		};
		PlayerDirection direction;

		// manejo de disparo
		enum AimPosition {AIM_UP,AIM_FRONT,AIM_DOWN,AIM_BODYTOGROUND,AIM_BACK,AIM_UP_BACK,AIM_DOWN_BACK,AIM_BODYTOGROUND_BACK};
		AimPosition aimingAt;

		//Manejo de balas
		Uint32 lastShotTime;
		Uint32 shotCooldown;
		int distanceToTravel = 425;

		// Manejo de balas
		std::list<Bullet*> bullets;
		std::list<Bullet*>::iterator bulletsIterator;

		CameraLogic* cameraLogic;
		ServerMessageHandler* serverMessageHandler;

		enum PlayerKeys {
			KEYCODE_UP,
			KEYCODE_DOWN,
			KEYCODE_RIGHT,
			KEYCODE_LEFT,
			KEYCODE_SPACE,
			KEYCODE_LCTRL,
			KEYCODE_N,
		};

		bool processedKeys = false; // Esto es para evitar procesar 2 mensajes que hayan llegado muy juntos en el mismo frame, y hacer que por ejemplo, el pj avanze el doble.
};

#endif /* PLAYER_HH_ */
