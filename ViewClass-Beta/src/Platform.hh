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
	//enum GroundType {GRASS, WOOD, ROCK, ICE};

	Platform(GameView* _gameView, string type, int pos_x, int pos_y, int pixels);
	virtual ~Platform();

	void render();
	list<Sprite*>* getListSpriteParts(){return &parts;}
	int getPosX(){return posX;}
	int getPosY(){return posY;}

private:
	GameView* gameView;
	string type; // probablemente no necesario

	std::list<Sprite*> parts;
	std::list<Sprite*>::iterator partsIterator;

	int posX, posY;
};

#endif /* PLATFORM_HH_ */
