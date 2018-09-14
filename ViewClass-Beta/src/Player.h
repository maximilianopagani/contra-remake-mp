/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

//#include "Headers.h"
#include "Sprite.h"
#include "GameView.h"
#include "Bullet.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
public:
	Player(GameView* view);
	virtual ~Player();

	// comunes al gameloop
	void update();
	void render();
	void destroy();

	int getPosX(){ return pos_x; }
	int getPosY(){ return pos_y; }

	//ACCIONES
	void jump();
	void walkLeft();
	void walkRight();
	void pointUP();
	void pointDown();
	void bodyToGround();
	void shoot();

private:
	int pos_x , pos_y , maxDistanceJump;
	static const int MAX_ANIMATIONS = 9;

	enum PlayerState {
		STATE_WALKINGRIGHT,
		STATE_WALKINGlEFT,
		STATE_STADING,
		STATE_JUMPINGUP,
		STATE_JUMPINGDOWN,
		STATE_POINTUP,
		STATE_POINTFRONT,
		STATE_POINTDOWN,
		STATE_POINTBODYTOGROUND
		};
	PlayerState state;

	// manejo de disparo
	enum AimPosition {AIM_UP,AIM_FRONT,AIM_DOWN,AIM_BODYTOGROUND,AIM_BACK};
	AimPosition aimingAt;
	Uint32 lastShotTime = 0;
	Uint32 shotCooldown = 200;

	// Manejo de balas
	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator bulletsIterator;

	GameView* gameView;
	Sprite* animations[MAX_ANIMATIONS];
	Sprite* bulletSprite;
};

#endif /* PLAYER_H_ */
