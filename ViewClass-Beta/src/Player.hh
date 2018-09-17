/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

//#include "Headers.h"
#include "Bullet.hh"
#include "GameView.hh"
#include "Sprite.hh"

#ifndef PLAYER_HH_
#define PLAYER_HH_

class Player
{
	public:

		Player(GameView* view);
		virtual ~Player();

		// comunes al gameloop
		void update();
		void render();
		void destroy();

		int getPosX(){ return pos_x; }
		int getPosY(){ return pos_y; }

		void spawn(int x, int y);

		//ACCIONES
		void jump();
		void walkLeft();
		void walkRight();
		void pointUP();
		void pointFront();
		void pointBack();
		void pointDown();
		void bodyToGround();
		void shoot();

		void handleKeys(const Uint8* _currentKeyStates);

	private:

		int pos_x, pos_y, maxDistanceJump;
		static const int MAX_ANIMATIONS = 14;

		enum PlayerState {
			STATE_WALKINGRIGHT,
			STATE_WALKINGLEFT,
			STATE_STANDING,
			STATE_JUMPINGUP,
			STATE_JUMPINGDOWN,
			STATE_POINTUP,
			STATE_POINTFRONT,
			STATE_POINTDOWN,
			STATE_POINTBODYTOGROUND,
			STATE_JUMPINGUP_BACK,
			STATE_JUMPINGDOWN_BACK,
			STATE_POINTUP_BACK,
			STATE_POINTDOWN_BACK,
			STATE_POINTBODYTOGROUND_BACK,
			};
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

		GameView* gameView;
		Sprite* animations[MAX_ANIMATIONS];
		Sprite* bulletSprite;

		const Uint8* currentKeyStates = NULL; // NO liberar/delete, es un puntero a un array interno de SDL
};

#endif /* PLAYER_HH_ */
