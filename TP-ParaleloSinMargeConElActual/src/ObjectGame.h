/*
 * ObjectGame.h
 *
 *  Created on: Sep 8, 2018
 *      Author: giova
 */

//#include "Headers.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#ifndef SRC_OBJECTGAME_H_
#define SRC_OBJECTGAME_H_

class ObjectGame {
public:
	ObjectGame();
	virtual ~ObjectGame();
	void update(int posCam);
	void render();
	void clean();
	void recorrido();
	void gotCollision();

	int getPosX(){ return pos_x ; }
	int getPosY(){ return pos_y ; }

private:
	SDL_Rect renderRect;
	SDL_Texture* renderTexture;
	int pos_x, pos_y;
	int speed_x;
	int posActualCamara_X=0;

};

#endif /* SRC_OBJECTGAME_H_ */
