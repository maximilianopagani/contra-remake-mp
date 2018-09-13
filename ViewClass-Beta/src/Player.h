/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Sprite.h"
#include <list>
#include "GameView.h"

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

	enum StatePlayer {
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
	StatePlayer state;

	enum AimPosition {AIM_UP,AIM_FRONT,AIM_DOWN,AIM_BODYTOGROUND};

	GameView* view = NULL;
	Sprite* animations[MAX_ANIMATIONS];
};

#endif /* PLAYER_H_ */
