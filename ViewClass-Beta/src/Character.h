/*
 * Character.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "SDLView.h"
#include "Sprite.h"
#include <list>

#ifndef CHARACTER_H_
#define CHARACTER_H_

class Character {
public:
	Character(SDL_View* view);
	virtual ~Character();
	void render();
	void posDerecha();

private:
	SDL_View* view = NULL;
	Sprite* sprite = NULL ;

	int pos_x , pos_y;
};

#endif /* CHARACTER_H_ */
