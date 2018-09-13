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
	//TODO funciones del jugador per se
	// jump

private:
	GameView* view = NULL;
	Sprite* sprite = NULL;

	int pos_x , pos_y;
};

#endif /* PLAYER_H_ */
