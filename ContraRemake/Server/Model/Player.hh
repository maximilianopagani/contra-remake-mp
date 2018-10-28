/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

//#include "Headers.h"

#ifndef PLAYER_HH_
#define PLAYER_HH_

#include "../../Utils/PlayerStateHandler.hh"
#include "../../Utils/Logger.hh"
#include "../../Utils/ICollisional.hh"
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

		void spawn(int x, int y);
		void freeze();
		void dragOfflinePlayer();

		//ACCIONES
		void jump();
		void goDown();
		void walkLeft();
		void walkRight();
		bool canMoveRight(int pixels_to_move);
		void pointUP(bool cond);
		void pointDefault(bool cond);
		void pointDown(bool cond);
		void bodyToGround();
		void normalState();
		void shoot();
		void fallingDownStop(){falling = false ;}
		void fallingDown(){falling = true ;}
		void wasHit(){ state = STATE_DEAD;};

		void handleKeys(const Uint8* playerKeyStates);
		bool alreadyProcessedKeys() { return processedKeys; }

		void setOnlineAgain() { state = STATE_STANDING; }
		bool isOnline() { return state != STATE_FREEZED; }
		bool isOffline() { return state == STATE_FREEZED; }

		void disableMovementBeyondBorder() { movement_beyond_border = false; }
		void enableMovementBeyondBorder() { movement_beyond_border = true; }
		bool canMoveBeyondBorder() { return movement_beyond_border; }

		list<Bullet*>* getBulletList(){ return &bullets; }

	private:

		int player_id;
		int pos_x, pos_y, maxDistanceJump;
		bool falling;

		Uint32 timeAtIterationStart=0;

		bool movement_beyond_border;

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
		int distanceToTravel = 375;

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
		};

		bool processedKeys = false; // Esto es para evitar procesar 2 mensajes que hayan llegado muy juntos en el mismo frame, y hacer que por ejemplo, el pj avanze el doble.
};

#endif /* PLAYER_HH_ */
