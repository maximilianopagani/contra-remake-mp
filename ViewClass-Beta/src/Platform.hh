/*
 * Platform.hh
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#ifndef PLATFORM_HH_
#define PLATFORM_HH_

#include "GameView.hh"
#include "Sprite.hh"

class Platform {

public:
	enum GroundType {GRASS, WOOD, ROCK};

	Platform(GameView* _gameView, GroundType type, int pos_x, int pos_y);
	virtual ~Platform();

	void render();

private:
	GameView* gameView;
	GroundType type; // probablemente no necesario
	Sprite* sprite;
	int posX, posY;
};

#endif /* PLATFORM_HH_ */