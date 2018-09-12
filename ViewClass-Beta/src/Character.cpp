/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Character.h"

Character::Character(SDL_View* _view) {
	view = _view;
	pos_x =200;
	pos_y =200;

	sprite = new Sprite(view,"imagenes/walking.png",128, 128, 128, 128, 512 );
}

Character::~Character() {}

void Character::posDerecha(){
	pos_x = 400;
}

void Character::render(){
	sprite->render(pos_x, pos_y);
}

